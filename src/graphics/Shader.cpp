#include "Debug.hpp"
#include "GL/glew.h"
#include "graphics/Shader.hpp"

namespace renderel::graphics {

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
    char *vertexShaderSource = loadFile(vertexShaderPath);
    char *fragmentShaderSource = loadFile(fragmentShaderPath);
    unsigned int vertexShaderID =
        CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShaderID =
        CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    m_RendererID = CreateProgram(vertexShaderID, fragmentShaderID);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const { glUseProgram(m_RendererID); }

void Shader::Unbind() const { glUseProgram(0); }

unsigned int Shader::CompileShader(const char *const shaderSource,
                                   unsigned int type) {
    GLCall(unsigned int shaderID = glCreateShader(type));
    GLCall(glShaderSource(shaderID, 1, &shaderSource, NULL));
    delete[] shaderSource;

    GLCall(glCompileShader(shaderID));

    int compilationResult = 0;
    GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult));
    if (compilationResult != GL_TRUE) {
        fprintf(stderr, "Failed to compile %s shader.\n",
                (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
        int infoLogLength = 0;
        GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));
        char log[1024];
        GLCall(glGetShaderInfoLog(shaderID, infoLogLength, NULL, log));
        fprintf(stderr, "Log: %s\n", log);
        GLCall(glDeleteShader(shaderID));
    }

    return shaderID;
}

char *Shader::loadFile(std::string path) {
    FILE *stream = fopen(path.c_str(), "rt");
    if (stream == NULL) {
        fprintf(stderr, "Couldn't open file %s\n", path.c_str());
        return NULL;
    }
    fseek(stream, 0, SEEK_END);
    unsigned long length = ftell(stream);
    char *shaderSource = new char[length + 1];
    shaderSource[length] = '\0';
    fseek(stream, 0, SEEK_SET);
    fread(shaderSource, 1, length, stream);
    fclose(stream);
    return shaderSource;
}

unsigned int Shader::CreateProgram(unsigned int vertexShaderID,
                                   unsigned int fragmentShaderID) {
    GLCall(unsigned int shaderID = glCreateProgram());
    GLCall(glAttachShader(shaderID, vertexShaderID));
    GLCall(glAttachShader(shaderID, fragmentShaderID));
    GLCall(glLinkProgram(shaderID));

    int result;
    GLCall(glGetProgramiv(shaderID, GL_LINK_STATUS, &result));
    if (result == GL_FALSE) {
        fprintf(stderr, "Failed to link program\n");
        return 0;
    }

    int infoLogLength;
    GLCall(glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));
    if (infoLogLength > 0) {
        char *log = (char *)malloc((infoLogLength + 1) * sizeof(char));
        if (log == NULL) {
            fprintf(stderr, "Couldn't allocate memory for shader log.");
            exit(EXIT_FAILURE);
        }
        GLCall(glGetProgramInfoLog(shaderID, infoLogLength, NULL, log));
        fprintf(stderr, "Log: %s\n", log);
        free(log);
    }

    GLCall(glDetachShader(shaderID, vertexShaderID));
    GLCall(glDetachShader(shaderID, fragmentShaderID));
    GLCall(glDeleteShader(vertexShaderID));
    GLCall(glDeleteShader(fragmentShaderID));

    return shaderID;
}

} // namespace renderel::graphics
