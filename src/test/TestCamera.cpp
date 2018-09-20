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
	  defaultCameraPosition(0.0f, 0.0f, -3.0f),

	  eulerAngle(0.0f, math::toRadians(90.0f), 0.0f),
	  aspectRatio(static_cast<float>(window->GetWidth()) / window->GetHeight()),
	  transform(math::Vec3<>(0.0f, 0.0f, 5.0f),
				math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), 0.0f),
				math::Vec3<>(1.0f)),

	  camera(Camera(defaultCameraPosition, 70.0f, aspectRatio, 0.1f, 100.0f)) {

	handler = static_cast<GameEventHandler *>(window->GetEventHandler());

	handler->AddKeyControl(KEY_W, yAxis, 1.0f);
	handler->AddKeyControl(KEY_S, yAxis, -1.0f);

	handler->AddKeyControl(KEY_D, xAxis, 1.0f);
	handler->AddKeyControl(KEY_A, xAxis, -1.0f);

	handler->AddKeyControl(KEY_R, zAxis, 1.0f);
	handler->AddKeyControl(KEY_SPACE, zAxis, 1.0f);
	handler->AddKeyControl(KEY_F, zAxis, -1.0f);

	handler->AddKeyControl(KEY_P, pause, 1.0f);

	va = new graphics::VertexArray();
	va = new graphics::VertexArray();

	vb = new graphics::VertexBuffer(static_cast<const float *>(m_Vertices),
									sizeof(m_Vertices));

	graphics::VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	va->AddBuffer(vb, layout);

	ib = new graphics::IndexBuffer<uint32>(indices, sizeof(indices) /
														sizeof(indices[0]));

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
	m_Window->EnableMouse();
}

static void ResetCursorPosition(const std::shared_ptr<Window> window,
								const GameEventHandler *handler,
								math::Vec2<> &lastPositionf) {
	math::Vec2<int32> newPosition = handler->GetMousePosition();
	math::Vec2<> newPositionf(
		static_cast<float>(newPosition.x) / window->GetWidth(),
		static_cast<float>(newPosition.y) / window->GetHeight());
	lastPositionf = newPositionf;
}

void TestCamera::OnUpdate(float deltaTime) {
	static bool first = true;
	static bool isPausable = true;
	static bool paused = false;

	static math::Vec2<> lastPositionf(0.5f);
	static math::Vec3<> lastForward;

	/* TODO: Not an elegant solution */
	if (pause.GetAmount() == 1.0f) {
		if (isPausable) {
			if (!paused) {
				lastForward = camera.GetForward();
				paused = true;
			} else {
				camera.SetForward(lastForward);
				ResetCursorPosition(m_Window, handler, lastPositionf);
				paused = false;
			}
			isPausable = false;
		}
	} else if (pause.GetAmount() == 0.0f) {
		isPausable = true;
	}

	if (first) {
		first = false;
		ResetCursorPosition(m_Window, handler, lastPositionf);
	}

	if (paused) {
		m_Window->EnableMouse();
	} else {
		m_Window->DisableMouse();

		math::Vec2<int32> newPosition = handler->GetMousePosition();
		math::Vec2<> newPositionf(
			static_cast<float>(newPosition.x) / m_Window->GetWidth(),
			static_cast<float>(newPosition.y) / m_Window->GetHeight());

		math::Vec2<> deltaPosition = lastPositionf - newPositionf;
		lastPositionf = newPositionf;

		eulerAngle.pitch += deltaPosition.y * rotationSensitivity * deltaTime;
		eulerAngle.yaw += deltaPosition.x * rotationSensitivity * deltaTime;

		eulerAngle.Normalize();

		math::Mat4<> view = camera.GetView();
		shader->Bind();
		shader->SetUniformMat4f("u_View", view);

		math::Vec3<> yVec =
			yAxis.GetAmount() * movementSensitivity * camera.GetForward();

		math::Vec3<> xVec = xAxis.GetAmount() * movementSensitivity *
							camera.GetForward().Cross(camera.GetUp());
		math::Vec3<> zVec =
			zAxis.GetAmount() * movementSensitivity * camera.GetUp();

		camera.SetPosition(camera.GetPosition() +
						   deltaTime * (yVec - xVec + zVec));

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
	ImGui::Text("P - Pause/Unpause");
	ImGui::Text("---------------");

	ImGui::SliderFloat("Rotation sensitivity", &rotationSensitivity, 0.0f,
					   300000.0f);
	ImGui::SliderFloat("Movement sensitivity", &movementSensitivity, 0.0f,
					   30.0f);

	if (ImGui::Button("Reset to defaults")) {
		movementSensitivity = defaultMovementSensitivity;
		rotationSensitivity = defaultRotationSensitivity;
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
