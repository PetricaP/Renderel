#ifndef OPENGLTEXTURE_HPP
#define OPENGLTEXTURE_HPP

#include "core/Common.hpp"
#include <GL/glew.h>
#include <string>

namespace renderel::graphics {

class OpenGLTexture {
  public:
	enum Target {
		TEXTURE_1D = GL_TEXTURE_1D,
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_3D = GL_TEXTURE_3D,
		TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
		TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
		TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
		TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE
	};

  private:
	std::string m_FilePath;
	uint32 m_RendererID = 0;
	uint8 *m_LocalBuffer = nullptr;
	int32 m_Width = 0;
	int32 m_Height = 0;
	int32 m_BPP = 0;
	Target m_Target;

  public:
	OpenGLTexture(const std::string &path, Target target);
	~OpenGLTexture();

	void Bind(uint32 slot = 0) const;
	void Unbind() const;

	int32 GetWidth() const { return m_Width; }
	int32 GetHeight() const { return m_Height; }
};

} // namespace renderel::graphics

#endif // OPENGLTEXTURE_HPP
