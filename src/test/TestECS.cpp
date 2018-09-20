#include "test/TestECS.hpp"
#include <imgui.h>

namespace renderel::test {

TestECS::TestECS(std::shared_ptr<Window> window) : Test(window) {
	TransformComponent transformComponent;
	transformComponent.transform.SetPosition(math::Vec3<>(0.0f, 0.0f, 3.0f));

	EntityHandle entity = m_ECS.MakeEntity(transformComponent);

	workingTransform =
		&m_ECS.GetComponent<TransformComponent>(entity)->transform;
}

void TestECS::OnUpdate(float deltaTime) {
	static float g = 0.0f;
	workingTransform->SetPosition(math::Vec3<>(g, g, g));
	g += 0.01;
}

void TestECS::OnGUIRender() {
	math::Vec3<> position = workingTransform->GetPosition();
	ImGui::Text("Position: x: %f y: %f z: %f", position.x, position.y,
				position.z);
}

void TestECS::OnRender() {}

} // namespace renderel::test
