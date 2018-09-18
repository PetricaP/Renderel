#include "test/TestCamera.hpp"
#include "math/Mat4.hpp"
#include "math/Math.hpp"
#include "math/Quaternion.hpp"
#include "math/Vec2.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace renderel::test {

TestCamera::TestCamera(const std::shared_ptr<Window> window)
	: Test(window), m_Color(0.2f, 0.2f, 0.2f, 1.0f),

	  transform(math::Vec3<>(0.0f, 0.0f, 5.0f),
				math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), 0.0f),
				math::Vec3<>(1.0f)),
	  eulerAngle(0.0f, math::toRadians(90.0f), 0.0f),
	  aspectRatio(static_cast<float>(window->GetWidth()) / window->GetHeight()),
	  position(math::Vec3<>(0.0f, 0.0f, -3.0f)),
	  camera(Camera(position, 70.0f, aspectRatio, 0.1f, 100.0f)) {

	handler = static_cast<GameEventHandler *>(window->GetEventHandler());

	handler->AddKeyControl(GLFW_KEY_W, yAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_S, yAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_D, xAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_A, xAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_R, zAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_SPACE, zAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_F, zAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_P, pause, 1.0f);
	handler->AddKeyControl(GLFW_KEY_U, pause, -1.0f);

	va = new graphics::VertexArray();
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

	shader->Bind();

	texture = new graphics::Texture("res/textures/bricks.jpg");
	texture->Bind(0);
	shader->SetUniform1i("u_Sampler", 0);

	math::Mat4<> model = transform.GetModel();
	shader->SetUniformMat4f("u_Model", model);

	math::Mat4<> proj = camera.GetProjection();
	shader->SetUniformMat4f("u_Proj", proj);
}

TestCamera::~TestCamera() {
	delete shader;
	delete va;
	delete ib;
	delete texture;
	delete renderer;
	glfwSetInputMode(static_cast<GLFWwindow *>(m_Window->GetAPIHandle()),
					 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void TestCamera::OnUpdate(float deltaTime) {

	if (pause.GetAmount() == 1.0f) {
		paused = true;
	} else if (pause.GetAmount() == -1.0f) {
		paused = false;
	}

	if (paused) {
		glfwSetInputMode(static_cast<GLFWwindow *>(m_Window->GetAPIHandle()),
						 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(static_cast<GLFWwindow *>(m_Window->GetAPIHandle()),
						 GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		transform.SetPosition(math::Vec3<>(0.0f, 0.0f, 4.0f));
		static math::Vec2<> lastPositionf(0.5f);

		math::Vec2<int> newPosition = handler->GetMousePosition();
		math::Vec2<> newPositionf(
			static_cast<float>(newPosition.x) / m_Window->GetWidth(),
			static_cast<float>(newPosition.y) / m_Window->GetHeight());

		math::Vec2<> deltaPosition = lastPositionf - newPositionf;
		lastPositionf = newPositionf;

		eulerAngle.pitch += deltaPosition.y * rotationSensitivity;
		eulerAngle.yaw += deltaPosition.x * rotationSensitivity;

		eulerAngle.Normalize();

		math::Mat4<> view = camera.GetView();
		shader->Bind();
		shader->SetUniformMat4f("u_View", view);

		position.x += xAxis.GetAmount() * deltaTime * 5.0f;
		position.y += yAxis.GetAmount() * deltaTime * 5.0f;
		position.z += zAxis.GetAmount() * deltaTime * 5.0f;

		camera.SetPosition(
			camera.GetPosition() +
			yAxis.GetAmount() * movementSensitivity * camera.GetForward() -
			xAxis.GetAmount() * movementSensitivity *
				camera.GetForward().Cross(camera.GetUp()) +
			zAxis.GetAmount() * movementSensitivity * camera.GetUp());
		camera.SetForward(eulerAngle.ToVector());
	}
}

void TestCamera::OnGUIRender() {
	ImGui::Text("W - Forward");
	ImGui::Text("S - Backwards");
	ImGui::Text("D - Right");
	ImGui::Text("A - Left");
	ImGui::Text("R/Space - Up");
	ImGui::Text("F - Down");
	ImGui::Text("P - Pause");
	ImGui::Text("U - Unpause");
	ImGui::Text("---------------");
	// TODO: add slider for rotation sensitivity (buggy)
	// ImGui::SliderFloat("Rotation sensitivity", &rotationSensitivity, 0.0f,
	// 2.0f);
	ImGui::SliderFloat("Movement sensitivity", &movementSensitivity, 0.0f,
					   3.0f);
	if (ImGui::Button("Reset to defaults")) {
		position = math::Vec3<>(0.0f, 0.0f, -3.0f);
		movementSensitivity = 0.2f;
		rotationSensitivity = 1.0f;
		eulerAngle.pitch = 0.0f;
		eulerAngle.yaw = math::toRadians(90.0f);
		eulerAngle.pitch = 0.0f;
	}
}

void TestCamera::OnRender() {
	graphics::Renderer<>::Clear();
	renderer->Submit(graphics::Renderable(va, ib, *shader));
	renderer->Flush();
}

} // namespace renderel::test
