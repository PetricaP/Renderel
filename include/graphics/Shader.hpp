#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include "math/Mat4.hpp"
#include <string>
#include <unordered_map>

namespace renderel::graphics {

class Shader {
  private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_LocationCache;

  public:
	Shader(const std::string &vertexShaderPath,
		   const std::string &fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string &name, float f0, float f1, float f2,
					  float f3);
	void SetUniform2f(const std::string &name, float f0, float f1);
	void SetUniformMat4f(const std::string &name, const math::Mat4<float> &mat);

  private:
	int GetUniformLocation(const std::string &name);
	static unsigned int CompileShader(const char *const shaderSource,
									  unsigned int type);
	static char *loadFile(std::string path);
	static unsigned int CreateProgram(unsigned int vertexShaderID,
									  unsigned int fragmentShaderID);
};

} // namespace renderel::graphics

#endif // GRAPHICS_SHADER_HPP
