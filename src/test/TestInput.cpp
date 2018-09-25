#include "test/TestInput.hpp"
#include "Debug.hpp"
#include <GL/glew.h>

namespace renderel::test {

TestInput::TestInput(const Window &window)
	: Test(window),
	  handler(static_cast<GameEventHandler *>(window.GetEventHandler())),
	  transform(
		  Transform<>(math::Vec3<>(0.0f, 0.0f, -5.0f),
					  math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), 0.0f),
					  math::Vec3<>(1.0f))),
	  shader("shaders/vertexShaderBasic2D.glsl",
			 "shaders/fragmentShaderBasic2D.glsl") {

	handler->AddKeyControl(KEY_W, yAxis, 1.0f);
	handler->AddKeyControl(KEY_S, yAxis, -1.0f);

	handler->AddKeyControl(KEY_D, xAxis, 1.0f);
	handler->AddKeyControl(KEY_A, xAxis, -1.0f);

	handler->AddKeyControl(KEY_R, zAxis, 1.0f);
	handler->AddKeyControl(KEY_F, zAxis, -1.0f);

	handler->AddKeyControl(KEY_Q, xRotation, 1.0f);
	handler->AddKeyControl(KEY_E, xRotation, -1.0f);

	handler->AddKeyControl(KEY_Z, yRotation, 1.0f);
	handler->AddKeyControl(KEY_X, yRotation, -1.0f);

	handler->AddKeyControl(KEY_C, zRotation, 1.0f);
	handler->AddKeyControl(KEY_V, zRotation, -1.0f);

	va = std::make_unique<graphics::VertexArray>();

	std::unique_ptr<graphics::VertexBuffer> vb =
		std::make_unique<graphics::VertexBuffer>(vertices, 3, sizeof(float) * 3);

	graphics::VertexBufferLayout layout;
	layout.Push<float>(3);

	va->AddBuffer(std::move(vb), layout);

	ib = std::make_unique<graphics::IndexBuffer>(indices, 3);
}

TestInput::~TestInput() {}

void TestInput::OnRender() {
	shader.Bind();
	va->Bind();
	ib->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, static_cast<int32>(ib->GetCount()),
						  GL_UNSIGNED_INT, nullptr));
}

void TestInput::OnUpdate(float deltaTime) {
	float aspectRatio =
		static_cast<float>(m_Window.GetWidth()) / m_Window.GetHeight();
	shader.Bind();
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 100.0f);
	shader.SetUniformMat4f("u_Proj", proj);

	static float x = 0.0f;
	static float y = 0.0f;
	static float z = 0.0f;

	x += xAxis.GetAmount() * deltaTime;
	y += yAxis.GetAmount() * deltaTime;
	z += zAxis.GetAmount() * deltaTime;

	rotation.x += xRotation.GetAmount() * deltaTime * 100.0f;
	rotation.y += yRotation.GetAmount() * deltaTime * 100.0f;
	rotation.z += zRotation.GetAmount() * deltaTime * 100.0f;

	transform.SetPosition(math::Vec3<>(x, y, z + -5.0f));

	transform.SetRotation(rotation);

	math::Mat4<> model = transform.GetModel();
	shader.Bind();
	shader.SetUniformMat4f("u_Model", model);
}

void TestInput::OnGUIRender() {
	GUI *gui = m_Window.GetGUI();
	gui->Text("W - Y forward");
	gui->Text("S - Y backward");
	gui->Text("D - X forward");
	gui->Text("A - X backward");
	gui->Text("R - Z forward");
	gui->Text("F - Z backward");
	gui->Text("---------------");
	gui->Text("Q - X rotate forward");
	gui->Text("E - x rotate backward");
	gui->Text("Z - Y rotate forward");
	gui->Text("X - Y rotate backward");
	gui->Text("C - Z rotate forward");
	gui->Text("V - Z rotate backward");
}

} // namespace renderel::test
