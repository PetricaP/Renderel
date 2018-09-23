#include "graphics/OpenGLTexture.hpp"
#include "Debug.hpp"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace renderel::graphics {

OpenGLTexture::OpenGLTexture(Target target, Filter filter, WrapMode wrapMode)
	: m_Target(target) {
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(target, m_RendererID));

	GLCall(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter));
	GLCall(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_R, wrapMode));

	GLCall(glBindTexture(target, 0));
}

OpenGLTexture::OpenGLTexture(const std::string &path, int32 components,
							 bool flipOnLoad, uint32 target, Filter filter,
							 WrapMode wrapMode, Format externalFormat,
							 Format internalFormat)
	: m_Target(target) {
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(target, m_RendererID));

	stbi_set_flip_vertically_on_load(flipOnLoad);
	uint8 *localBuffer =
		stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, components);
	if (localBuffer == nullptr) {
		DEBUG_LOG("Texture", ERROR, "Couldn't load texture from file %s.",
				  path.c_str());
		return;
	}

	GLCall(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter));
	GLCall(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode));

	GLCall(glTexImage2D(target, 0, internalFormat, m_Width, m_Height, 0,
						externalFormat, GL_UNSIGNED_BYTE, localBuffer));

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}

	GLCall(glBindTexture(target, 0));
}

void OpenGLTexture::AddPart(const std::string &path, bool flipOnLoad,
							int32 components, uint32 target,
							Format externalFormat, Format internalFormat) {

	stbi_set_flip_vertically_on_load(flipOnLoad);
	uint8 *localBuffer =
		stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, components);
	if (localBuffer == nullptr) {
		DEBUG_LOG("Texture", ERROR, "Couldn't load texture from file %s.",
				  path.c_str());
		return;
	}

	Bind();

	GLCall(glTexImage2D(target, 0, internalFormat, m_Width, m_Height, 0,
						externalFormat, GL_UNSIGNED_BYTE, localBuffer));

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}

	Unbind();
}

OpenGLTexture::~OpenGLTexture() { GLCall(glDeleteTextures(1, &m_RendererID)); }

void OpenGLTexture::Bind(uint32 slot /*= 0*/) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(m_Target, m_RendererID));
}

void OpenGLTexture::Unbind() const { GLCall(glBindTexture(m_Target, 0)); }

} // namespace renderel::graphics
