#include "test/TestInput.hpp"
#include "Debug.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace renderel::test {

TestInput::TestInput(const std::shared_ptr<Window> window)
	: Test(window),
	  handler(static_cast<GameEventHandler *>(window->GetEventHandler())),
	  transform(
		  Transform<>(math::Vec3<>(0.0f, 0.0f, -5.0f),
					  math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), 0.0f),
					  math::Vec3<>(1.0f))) {

	handler->AddKeyControl(GLFW_KEY_W, yAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_S, yAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_D, xAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_A, xAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_T, zAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_R, zAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_Q, xRotation, 1.0f);
	handler->AddKeyControl(GLFW_KEY_R, xRotation, -1.0f);

	handler->AddKeyControl(GLFW_KEY_Z, yRotation, 1.0f);
	handler->AddKeyControl(GLFW_KEY_C, yRotation, -1.0f);

	handler->AddKeyControl(GLFW_KEY_C, zRotation, 1.0f);
	handler->AddKeyControl(GLFW_KEY_V, zRotation, -1.0f);

	va = new graphics::VertexArray();

	graphics::VertexBuffer *vb =
		new graphics::VertexBuffer(vertices, sizeof(vertices));

	graphics::VertexBufferLayout layout;
	layout.Push<float>(3);

	va->AddBuffer(vb, layout);

	ib = new graphics::IndexBuffer<>(indices, 3);

	shader = new graphics::Shader("shaders/vertexShaderBasic2D.glsl",
								  "shaders/fragmentShaderBasic2D.glsl");
	float aspectRatio =
		static_cast<float>(window->GetWidth()) / window->GetHeight();
	shader->Bind();
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 100.0f);
	shader->SetUniformMat4f("u_Proj", proj);
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

	transform.SetRotation(
		math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), rotation.x) *
		math::Quaternion<>(math::Vec3<>(0.0f, 1.0f, 0.0f), rotation.y) *
		math::Quaternion<>(math::Vec3<>(0.0f, 0.0f, 1.0f), rotation.z));

	math::Mat4<> model = transform.GetModel();
	shader->Bind();
	shader->SetUniformMat4f("u_Model", model);
}

} // namespace renderel::test
