#include "test/TestTexturedCube.hpp"
#include "Transform.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"

#define WIDTH 1080
#define HEIGHT 720

namespace renderel::test {

TestTexturedCube::TestTexturedCube() : m_Color{0.1f, 0.1f, 0.4f, 1.0f} {
	va = new graphics::VertexArray();

	vb = new graphics::VertexBuffer(static_cast<const float *>(m_Vertices),
									sizeof(m_Vertices));

	graphics::VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	va->AddBuffer(vb, layout);

	ib = new graphics::IndexBuffer<unsigned int>(
		indices, sizeof(indices) / sizeof(indices[0]));

	renderer = new graphics::BasicRenderer();
	shader = new graphics::Shader("shaders/vertexShader.glsl",
								  "shaders/fragmentShaderTexture.glsl");
	Transform<> transform(
		math::Vec3<>(0.0f, 0.0f, -5.0f),
		math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), 20.0f) *
			math::Quaternion<>(math::Vec3<>(0.0f, 1.0f, 0.0f), 30.0f) *
			math::Quaternion<>(math::Vec3<>(0.0f, 0.0f, 1.0f), 10.0f),
		math::Vec3<>(1.0f));

	shader->Bind();
	texture = new graphics::Texture("res/textures/bricks.jpg");
	texture->Bind();
	shader->SetUniform1i("u_Sampler", 0);

	math::Mat4<> model = transform.GetModel();
	shader->SetUniformMat4f("u_Model", model);

	float aspectRatio = 1.0f * WIDTH / HEIGHT;
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 100.0f);
	shader->SetUniformMat4f("u_Proj", proj);
}

TestTexturedCube::~TestTexturedCube() {
	delete shader;
	delete va;
	delete ib;
	delete renderer;
}

void TestTexturedCube::OnRender() {
	graphics::Renderer<>::SetClearColor(m_Color.r, m_Color.g, m_Color.b,
										m_Color.a);
	graphics::Renderer<>::Clear();
	renderer->Submit(graphics::Renderable(va, ib, *shader));
	renderer->Flush();
}

} // namespace renderel::test
