#include "test/TestTexturedCube.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"

namespace renderel::test {

TestTexturedCube::TestTexturedCube(const Window &window)
	: Test(window), m_Color{0.1f, 0.1f, 0.2f, 1.0f},
	  shader("shaders/vertexShader.glsl", "shaders/fragmentShaderTexture.glsl"),
	  texture("res/textures/cpp_logo.png"), rotation(0.0f, 0.0f, 0.0f),
	  transform(
		  math::Vec3<>(0.0f, 0.0f, -5.0f),
		  math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), rotation.x) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 1.0f, 0.0f), rotation.y) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 0.0f, 1.0f), rotation.z),
		  math::Vec3<>(1.0f)) {

	va = std::make_unique<graphics::VertexArray>();

	vb = std::make_unique<graphics::VertexBuffer>(
		static_cast<const float *>(m_Vertices), sizeof(m_Vertices));

	graphics::VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	va->AddBuffer(std::move(vb), layout);

	ib = std::make_unique<graphics::IndexBuffer<>>(
		indices, sizeof(indices) / sizeof(indices[0]));

	shader.Bind();

	texture.Bind();
	shader.SetUniform1i("u_Sampler", 0);

	math::Mat4<> model = transform.GetModel();
	shader.SetUniformMat4f("u_Model", model);
}

TestTexturedCube::~TestTexturedCube() {}

void TestTexturedCube::OnUpdate(float) {
	float aspectRatio = 1.0f * m_Window.GetWidth() / m_Window.GetHeight();
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 100.0f);
	shader.SetUniformMat4f("u_Proj", proj);

	transform.SetRotation(rotation);

	math::Mat4<> model = transform.GetModel();
	shader.SetUniformMat4f("u_Model", model);
}

void TestTexturedCube::OnGUIRender() {
	GUI *gui = m_Window.GetGUI();
	gui->Slider3f("Position", &transform.GetPosition().x, -5.0f, 5.0f);
	gui->Slider3f("Rotation", &rotation.x, -180.0f, 180.0f);
	gui->Slider3f("Scale", &transform.GetScale().x, 0.0f, 10.0f);

	if (gui->Button("Reset to defaults")) {
		transform.SetPosition(math::Vec3<>(0.0f, 0.0f, -5.0f));
		rotation.x = 0;
		rotation.y = 0;
		rotation.z = 0;
		transform.SetScale(math::Vec3<>(1.0f));
	}
}

void TestTexturedCube::OnRender() {
	graphics::Renderer<>::Clear();
	renderer.Submit(graphics::Renderable(va.get(), ib.get(), shader));
	renderer.Flush();
}

} // namespace renderel::test
