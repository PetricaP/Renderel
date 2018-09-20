#include "graphics/Shader.hpp"
#include "Debug.hpp"
#include "GL/glew.h"
#include <iostream>

namespace renderel::graphics {

Shader::Shader(const std::string &vertexShaderPath,
			   const std::string &fragmentShaderPath) {
	char *vertexShaderSource = loadFile(vertexShaderPath);
	char *fragmentShaderSource = loadFile(fragmentShaderPath);

	uint32 vertexShaderID = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
	uint32 fragmentShaderID =
		CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	m_RendererID = CreateProgram(vertexShaderID, fragmentShaderID);
}

Shader::~Shader() { glDeleteProgram(m_RendererID); }

void Shader::Bind() const { glUseProgram(m_RendererID); }

void Shader::Unbind() const { glUseProgram(0); }

uint32 Shader::CompileShader(const char *const shaderSource, uint32 type) {
	GLCall(uint32 shaderID = glCreateShader(type));
	GLCall(glShaderSource(shaderID, 1, &shaderSource, nullptr));
	delete[] shaderSource;

	GLCall(glCompileShader(shaderID));

	int32 compilationResult = 0;
	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult));
	if (compilationResult != GL_TRUE) {
		DEBUG_LOG("Shaders", ERROR, "Failed to compile %s shader",
				  (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");

		int32 infoLogLength = 0;
		GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));
		char log[1024];
		GLCall(glGetShaderInfoLog(shaderID, infoLogLength, nullptr, log));
		DEBUG_LOG("Shaders", WARNING, "Log: %s", log);

		GLCall(glDeleteShader(shaderID));
	}

	return shaderID;
}

char *Shader::loadFile(std::string path) {
	FILE *stream = fopen(path.c_str(), "rt");
	if (stream == nullptr) {
		DEBUG_LOG("Shaders", ERROR, "Failed to open shader: %s", path.c_str());
		return nullptr;
	}

	fseek(stream, 0, SEEK_END);
	unsigned long length = static_cast<unsigned long>(ftell(stream));

	char *shaderSource = new char[length + 1];
	shaderSource[length] = '\0';
	fseek(stream, 0, SEEK_SET);
	fread(shaderSource, 1, length, stream);
	fclose(stream);

	return shaderSource;
}

uint32 Shader::CreateProgram(uint32 vertexShaderID, uint32 fragmentShaderID) {
	GLCall(uint32 shaderID = glCreateProgram());
	GLCall(glAttachShader(shaderID, vertexShaderID));
	GLCall(glAttachShader(shaderID, fragmentShaderID));
	GLCall(glLinkProgram(shaderID));

	int32 result;
	GLCall(glGetProgramiv(shaderID, GL_LINK_STATUS, &result));
	if (result == GL_FALSE) {
		DEBUG_LOG("Shaders", ERROR, "Failed to link program.");

		int32 infoLogLength;
		GLCall(glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));

		if (infoLogLength > 0) {
			char *log = static_cast<char *>(
				malloc(static_cast<unsigned long>((infoLogLength + 1)) *
					   sizeof(char)));
			if (log == nullptr) {
				DEBUG_LOG("Shaders", ERROR,
						  "Couldn't allocate memory for shader log");
				exit(EXIT_FAILURE);
			}
			GLCall(glGetProgramInfoLog(shaderID, infoLogLength, nullptr, log));
			DEBUG_LOG("Shaders", WARNING, "Log: %s", log);
			free(log);
		}
		return 0;
	}

	GLCall(glDetachShader(shaderID, vertexShaderID));
	GLCall(glDetachShader(shaderID, fragmentShaderID));
	GLCall(glDeleteShader(vertexShaderID));
	GLCall(glDeleteShader(fragmentShaderID));

	return shaderID;
}

int32 Shader::GetUniformLocation(const std::string &name) {
	if (m_LocationCache.find(name) != m_LocationCache.end()) {
		return m_LocationCache[name];
	}
	GLCall(int32 location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1) {
		DEBUG_LOG("Shaders", WARNING, "Uniform %s might not exist.",
				  name.c_str());
	}
	m_LocationCache[name] = location;
	return location;
}

void Shader::SetUniform4f(const std::string &name, float f0, float f1, float f2,
						  float f3) {
	GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniform2f(const std::string &name, float f0, float f1) {
	GLCall(glUniform2f(GetUniformLocation(name), f0, f1));
}

void Shader::SetUniformMat4f(const std::string &name,
							 const math::Mat4<float> &mat) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE,
							  &mat.elements[0][0]));
}

void Shader::SetUniform1i(const std::string &name, int32 val) {
	GLCall(glUniform1i(GetUniformLocation(name), val));
}

} // namespace renderel::graphics
