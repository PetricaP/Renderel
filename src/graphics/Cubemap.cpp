#include "graphics/Cubemap.hpp"
#include "Debug.hpp"
#include "graphics/Renderer.hpp"
#include <GL/glew.h>

namespace renderel::graphics {

Cubemap::Cubemap(const std::vector<std::string> &faces,
				 const std::string &vertexShaderPath,
				 const std::string &fragmentShaderPath)
	: m_Shader(vertexShaderPath, fragmentShaderPath),
	  m_Texture(Texture::TEXTURE_CUBE_MAP, Texture::LINEAR,
				Texture::CLAMP_TO_EDGE),
	  m_ViewMatrix(math::Mat4<float>(1.0f)),
	  m_ProjectionMatrix(math::Mat4<float>(1.0f)) {

	ASSERT(faces.size() == 6);
	m_Texture.Bind();

	for (uint32 i = 0; i < faces.size(); ++i) {
		m_Texture.AddPart(faces[i], false, 3,
						  Texture::TEXTURE_CUBE_MAP_POSITIVE_X + i,
						  Texture::RGB, Texture::RGB8);
	}

	m_Va = std::make_unique<VertexArray>();

	VertexBufferLayout vbl;
	vbl.Push<float>(3);

	m_Vb = std::make_unique<VertexBuffer>(
		m_SkyboxVertices, sizeof(m_SkyboxVertices) / 3 / sizeof(float),
		3 * sizeof(float));

	m_Va->AddBuffer(std::move(m_Vb), vbl);
}

Cubemap::~Cubemap() {}

void Cubemap::Draw() {
	Renderer::DisableDepthMask();
	m_Shader.Bind();

	m_Shader.SetUniformMat4f("u_View", m_ViewMatrix);
	m_Shader.SetUniformMat4f("u_Proj", m_ProjectionMatrix);

	m_Va->Bind();
	m_Texture.Bind();

	renderer.Submit(Renderable(m_Shader, m_Va.get()));
	renderer.Flush();

	Renderer::EnableDepthMask();
}

void Cubemap::SetViewMatrix(const math::Mat4<float> &mat) {
	m_ViewMatrix = mat;
}

void Cubemap::SetProjectionMatrix(const math::Mat4<float> &mat) {
	m_ProjectionMatrix = mat;
}

} // namespace renderel::graphics
