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
		TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
		TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
		TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE
	};

	enum Filter {
		LINEAR = GL_LINEAR,
		NEARENST = GL_NEAREST,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};

	enum WrapMode {
		REPEAT = GL_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	};

	enum Format {
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		RGB8 = GL_RGB8,
		RGBA8 = GL_RGBA8
	};

  private:
	uint32 m_RendererID = 0;
	uint32 m_Target;
	int32 m_Width, m_Height, m_BPP;

  public:
	OpenGLTexture(Target target, Filter filter, WrapMode wrapMode);

	OpenGLTexture(const std::string &path, int32 components = 4,
				  bool flipOnLoad = true, uint32 target = TEXTURE_2D,
				  Filter filter = LINEAR, WrapMode wrapMode = REPEAT,
				  Format externalFormat = RGBA, Format internalFormat = RGBA8);

	void AddPart(const std::string &path, bool flipOnLoad, int32 components,
				 uint32 target, Format externalFormat, Format internalFormat);
	~OpenGLTexture();

	void Bind(uint32 slot = 0) const;
	void Unbind() const;
};

} // namespace renderel::graphics

#endif // OPENGLTEXTURE_HPP
