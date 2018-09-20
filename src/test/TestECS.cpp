#include "test/TestECS.hpp"
#include "graphics/Shader.hpp"

namespace renderel::test {

TestECS::TestECS(std::shared_ptr<Window> window)
	: Test(window), shader("shaders/vertexShader.glsl",
						   "shaders/fragmentShaderTexture.glsl") {

	TransformComponent transformComponent;
	transformComponent.transform.SetPosition(math::Vec3<>(0.0f, 0.0f, 3.0f));

	RenderableMeshComponent renderableMeshComponent;
	renderableMeshComponent.mesh.LoadOBJ("res/models/monkey.obj");

	entity = m_ECS.MakeEntity(transformComponent, renderableMeshComponent);

	shader.Bind();
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
	m_Window->GetGUI()->Text("Position: x: %f y: %f z: %f", position.x,
							 position.y, position.z);
}

void TestECS::OnRender() {
	Transform<> transform =
		m_ECS.GetComponent<TransformComponent>(entity)->transform;
	graphics::Mesh<> mesh =
		m_ECS.GetComponent<RenderableMeshComponent>(entity)->mesh;

	renderer.Submit(graphics::Renderable<>(mesh.GetVertexArray(),
										   mesh.GetIndexBuffer(), shader));
	renderer.Flush();
}

} // namespace renderel::test
