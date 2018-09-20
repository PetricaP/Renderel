#include "graphics/Cubemap.hpp"

#include "Debug.hpp"
#include <GL/glew.h>
#include <iostream>
#include <stb_image.h>

namespace renderel::graphics {

Cubemap::Cubemap(const std::vector<std::string> &faces,
				 const std::string &vertexShaderPath,
				 const std::string &fragmentShaderPath)
	: m_ViewMatrix(math::Mat4<float>(1.0f)),
	  m_ProjectionMatrix(math::Mat4<float>(1.0f)) {

	ASSERT(faces.size() == 6);

	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));

	stbi_set_flip_vertically_on_load(false);

	for (uint32 i = 0; i < faces.size(); ++i) {
		int32 width, height, channels;
		unsigned char *data =
			stbi_load(faces[i].c_str(), &width, &height, &channels, 0);

		if (data) {
			GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
								width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
								data));
		} else {
			std::cerr << "Failed to load texture " << faces[i].c_str()
					  << std::endl;
		}
		stbi_image_free(data);
	}

	GLCall(
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

	GLCall(
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,
						   GL_CLAMP_TO_EDGE));

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,
						   GL_CLAMP_TO_EDGE));

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,
						   GL_CLAMP_TO_EDGE));

	m_Shader = new Shader(vertexShaderPath, fragmentShaderPath);

	m_Va = new VertexArray();
	m_Vb = new VertexBuffer(m_SkyboxVertices, sizeof(m_SkyboxVertices));

	VertexBufferLayout vbl;
	vbl.Push<float>(3);

	m_Va->AddBuffer(m_Vb, vbl);
}

Cubemap::~Cubemap() {
	delete m_Shader;
	delete m_Va;
	// m_Vb is deleted by m_Va
}

void Cubemap::Draw() const {
	GLCall(glDepthMask(GL_FALSE));
	m_Shader->Bind();

	this->m_Shader->SetUniformMat4f("u_View", m_ViewMatrix);
	this->m_Shader->SetUniformMat4f("u_Proj", m_ProjectionMatrix);

	m_Va->Bind();
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));

	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	GLCall(glDepthMask(GL_TRUE));
}

void Cubemap::SetViewMatrix(const math::Mat4<float> &mat) {
	m_ViewMatrix = mat;
}

void Cubemap::SetProjectionMatrix(const math::Mat4<float> &mat) {
	this->m_ProjectionMatrix = mat;
}

} // namespace renderel::graphics
