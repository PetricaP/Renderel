#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <string>

namespace renderel::graphics {

class Shader {
  private:
    unsigned int m_RendererID;

  public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    void Bind() const;
    void Unbind() const;

  private:
    static unsigned int CompileShader(const char *const shaderSource,
                                      unsigned int type);
    static char *loadFile(std::string path);
    static unsigned int CreateProgram(unsigned int vertexShaderID,
                                      unsigned int fragmentShaderID);
};

} // namespace renderel::graphics

#endif // GRAPHICS_SHADER_HPP
