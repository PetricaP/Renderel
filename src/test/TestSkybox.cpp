#include "test/TestSkybox.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <vector>

namespace renderel::test {

TestSkybox::TestSkybox(const std::shared_ptr<Window> window)
	: TestOBJLoader(window, "res/models/dome.obj",
					"res/textures/chesterfield_normal.png",
					"shaders/normalShader.vert", "shaders/normalShader.frag"),
	  m_Camera(math::Vec3<>(0.0f, 0.0f, 0.0f), 70.0f, 1.21f, 0.001f, 100.0f),
	  eulerAngle(0.0f, -90.0f, 0.0f) {

	handler = static_cast<GameEventHandler *>(window->GetEventHandler());

	std::vector<std::string> faces;
	std::vector<std::string> shaders;

	handler->AddKeyControl(KEY_W, yAxis, 1.0f);
	handler->AddKeyControl(KEY_S, yAxis, -1.0f);

	handler->AddKeyControl(KEY_D, xAxis, 1.0f);
	handler->AddKeyControl(KEY_A, xAxis, -1.0f);

	handler->AddKeyControl(KEY_R, zAxis, 1.0f);
	handler->AddKeyControl(KEY_SPACE, zAxis, 1.0f);
	handler->AddKeyControl(KEY_F, zAxis, -1.0f);

	handler->AddKeyControl(KEY_Q, toggleMouse, 1.0f);

	// faces.push_back("res/textures/cm/cm_right.jpg");
	// faces.push_back("res/textures/cm/cm_left.jpg");
	// faces.push_back("res/textures/cm/cm_top.jpg");
	// faces.push_back("res/textures/cm/cm_bottom.jpg");
	// faces.push_back("res/textures/cm/cm_front.jpg");
	// faces.push_back("res/textures/cm/cm_back.jpg");

	faces.push_back("res/textures/cm/right.jpg");
	faces.push_back("res/textures/cm/left.jpg");
	faces.push_back("res/textures/cm/top.jpg");
	faces.push_back("res/textures/cm/bottom.jpg");
	faces.push_back("res/textures/cm/front.jpg");
	faces.push_back("res/textures/cm/back.jpg");

	// faces.push_back("res/textures/cm/lake_right.jpg");
	// faces.push_back("res/textures/cm/lake_left.jpg");
	// faces.push_back("res/textures/cm/lake_top.jpg");
	// faces.push_back("res/textures/cm/lake_bottom.jpg");
	// faces.push_back("res/textures/cm/lake_front.jpg");
	// faces.push_back("res/textures/cm/lake_back.jpg");

	m_Cubemap = new graphics::Cubemap(faces, "shaders/cubemap.vert",
									  "shaders/cubemap.frag");

	texture->Bind(1);
	shader->SetUniform1i("u_Texture", 1);
	// shader->SetUniform1i("u_Cubemap", m_Cubemap->GetTextureID());
}

TestSkybox::~TestSkybox() { delete m_Cubemap; }

void TestSkybox::OnRender() {
	math::Vec3 position = m_Camera.GetPosition();
	shader->SetUniform3f("u_CameraPosition", position.x, position.y,
						 position.z);
	TestOBJLoader::OnRender();
	m_Cubemap->Draw();
}

void TestSkybox::OnGUIRender() {

	ImGui::Text("Q - Toggle Mouse");
	ImGui::Text("Euler angle yaw: %f", eulerAngle.yaw);
	ImGui::Text("Euler angle pitch: %f", eulerAngle.pitch);
	ImGui::Text("Euler angle roll: %f", eulerAngle.roll);
	ImGui::Text("Camera position:\n\t%.1f\n\t%.1f\n\t%.1f",
				m_Camera.GetPosition().x, m_Camera.GetPosition().y,
				m_Camera.GetPosition().z);
}

void TestSkybox::OnUpdate(float deltaTime) {

	if (toggleMouse.GetAmount()) {
		if (canChangeMouse) {
			if (hasCursor) {
				m_Window->DisableMouse();
			} else {
				m_Window->EnableMouse();
			}
			hasCursor = !hasCursor; // reverse hasCursor
			canChangeMouse = false;
		}
	} else {
		canChangeMouse = true;
	}

	math::Vec3<> yVec =
		yAxis.GetAmount() * movementSensitivity * m_Camera.GetForward();

	math::Vec3<> xVec = xAxis.GetAmount() * movementSensitivity *
						m_Camera.GetForward().Cross(m_Camera.GetUp());
	math::Vec3<> zVec =
		zAxis.GetAmount() * movementSensitivity * m_Camera.GetUp();

	m_Camera.SetPosition(m_Camera.GetPosition() +
						 deltaTime * (yVec - xVec + zVec));

	static math::Vec2<> lastPositionf(0.5f);
	static math::Vec3<> lastForward;

	math::Vec2<int> newPosition = handler->GetMousePosition();
	math::Vec2<> newPositionf(
		static_cast<float>(newPosition.x) / m_Window->GetWidth(),
		static_cast<float>(newPosition.y) / m_Window->GetHeight());

	math::Vec2<> deltaPosition = lastPositionf - newPositionf;
	lastPositionf = newPositionf;

	if (!hasCursor) {
		if (inputReady) {
			eulerAngle.pitch +=
				deltaPosition.y * rotationSensitivity * deltaTime;
			eulerAngle.yaw += deltaPosition.x * rotationSensitivity * deltaTime;

			eulerAngle.Normalize();
		} else {
			inputReady = true;
		}
	}
	m_Camera.SetForward(eulerAngle.ToVector());

	math::Mat4<> view = m_Camera.GetView();
	shader->Bind();
	shader->SetUniformMat4f("u_View", view);

	m_Cubemap->SetViewMatrix(m_Camera.GetView().StripTranslation());
	m_Cubemap->SetProjectionMatrix(m_Camera.GetProjection());

	rotation.y += deltaTime * 15.0f;
	if (rotation.y > 360.0f) {
		rotation.y -= 360.0f;
	}
	TestOBJLoader::OnUpdate(deltaTime);
}

} // namespace renderel::test