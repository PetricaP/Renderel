#include "test/TestInput.hpp"
#include "Debug.hpp"
#include <GL/glew.h>
#include <imgui.h>

namespace renderel::test {

TestInput::TestInput(const std::shared_ptr<Window> window)
	: Test(window),
	  handler(static_cast<GameEventHandler *>(window->GetEventHandler())),
	  transform(
		  Transform<>(math::Vec3<>(0.0f, 0.0f, -5.0f),
					  math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), 0.0f),
					  math::Vec3<>(1.0f))) {

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

	va = new graphics::VertexArray();

	graphics::VertexBuffer *vb =
		new graphics::VertexBuffer(vertices, sizeof(vertices));

	graphics::VertexBufferLayout layout;
	layout.Push<float>(3);

	va->AddBuffer(vb, layout);

	ib = new graphics::IndexBuffer<>(indices, 3);

	shader = new graphics::Shader("shaders/vertexShaderBasic2D.glsl",
								  "shaders/fragmentShaderBasic2D.glsl");
}

TestInput::~TestInput() {
	delete va;
	delete ib;
	delete shader;
}

void TestInput::OnRender() {
	shader->Bind();
	va->Bind();
	ib->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, static_cast<int>(ib->GetCount()),
						  GL_UNSIGNED_INT, nullptr));
}

void TestInput::OnUpdate(float deltaTime) {
	float aspectRatio =
		static_cast<float>(m_Window->GetWidth()) / m_Window->GetHeight();
	shader->Bind();
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 100.0f);
	shader->SetUniformMat4f("u_Proj", proj);

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
	shader->Bind();
	shader->SetUniformMat4f("u_Model", model);
}

void TestInput::OnGUIRender() {
	ImGui::Text("W - Y forward");
	ImGui::Text("S - Y backward");
	ImGui::Text("D - X forward");
	ImGui::Text("A - X backward");
	ImGui::Text("R - Z forward");
	ImGui::Text("F - Z backward");
	ImGui::Text("---------------");
	ImGui::Text("Q - X rotate forward");
	ImGui::Text("E - x rotate backward");
	ImGui::Text("Z - Y rotate forward");
	ImGui::Text("X - Y rotate backward");
	ImGui::Text("C - Z rotate forward");
	ImGui::Text("V - Z rotate backward");
}

} // namespace renderel::test
