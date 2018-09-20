#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include "core/Common.hpp"
#include "math/Mat4.hpp"
#include <string>
#include <unordered_map>

namespace renderel::graphics {

class Shader {
  private:
	uint32 m_RendererID;
	std::unordered_map<std::string, int32> m_LocationCache;

  public:
	Shader(const std::string &vertexShaderPath,
		   const std::string &fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string &name, int32 val);
	void SetUniform4f(const std::string &name, float f0, float f1, float f2,
					  float f3);
	void SetUniform2f(const std::string &name, float f0, float f1);
	void SetUniformMat4f(const std::string &name, const math::Mat4<float> &mat);

  private:
	int32 GetUniformLocation(const std::string &name);
	static uint32 CompileShader(const char *const shaderSource, uint32 type);
	static char *loadFile(std::string path);
	static uint32 CreateProgram(uint32 vertexShaderID, uint32 fragmentShaderID);
};

} // namespace renderel::graphics

#endif // GRAPHICS_SHADER_HPP
