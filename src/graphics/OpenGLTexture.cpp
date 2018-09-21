#include "graphics/OpenGLTexture.hpp"
#include "Debug.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <stb_image.h>

namespace renderel::graphics {

OpenGLTexture::OpenGLTexture(const std::string &path, Target target)
	: m_FilePath(path), m_Target(target) {
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(target, m_RendererID));

	GLCall(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glTexImage2D(target, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
						GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(target, 0));

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

OpenGLTexture::~OpenGLTexture() { GLCall(glDeleteTextures(1, &m_RendererID)); }

void OpenGLTexture::Bind(uint32 slot /*= 0*/) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(m_Target, m_RendererID));
}

void OpenGLTexture::Unbind() const { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); }

} // namespace renderel::graphics
