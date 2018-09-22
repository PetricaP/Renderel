#include "test/TestECS.hpp"
#include "graphics/Shader.hpp"

namespace renderel::test {

TestECS::TestECS(const Window &window)
	: Test(window),
	  shader("shaders/vertexShader.glsl", "shaders/fragmentShaderTexture.glsl"),
	  texture("res/textures/monkey_baked.png") {

	renderableMeshComponent.mesh.LoadOBJ("res/models/monkey.obj");
	cameraComponent.camera.SetUp(math::Vec3<>(0.0f, 0.0f, -3.0f), 70.0f, 1.23f,
								 0.1f, 100.0f);

	transformComponent.transform.SetPosition(math::Vec3<>(0.0f, 0.0f, 5.0f));
	transformComponent.transform.SetRotation(
		math::Quaternion<>(math::Vec3<>(0.0f, 1.0f, 0.0f), 180.0f));

	entity = m_ECS.MakeEntity(renderableMeshComponent, transformComponent,
							  cameraComponent);

	texture.Bind();
	shader.Bind();
	math::Mat4<> view =
		m_ECS.GetComponent<CameraComponent>(entity)->camera.GetView();
	math::Mat4<> proj =
		m_ECS.GetComponent<CameraComponent>(entity)->camera.GetProjection();

	shader.SetUniformMat4f("u_View", view);
	shader.SetUniformMat4f("u_Proj", proj);
}

void TestECS::OnUpdate(float) {
	math::Mat4<> model =
		m_ECS.GetComponent<TransformComponent>(entity)->transform.GetModel();
	shader.SetUniformMat4f("u_Model", model);
}

void TestECS::OnGUIRender() {
	math::Vec3<> position =
		m_ECS.GetComponent<TransformComponent>(entity)->transform.GetPosition();
	m_Window.GetGUI()->Text("Position: x: %f y: %f z: %f", position.x,
							position.y, position.z);
}

void TestECS::OnRender() {
	graphics::Mesh<> &mesh =
		m_ECS.GetComponent<RenderableMeshComponent>(entity)->mesh;

	renderer.Submit(graphics::Renderable<>(mesh.GetVertexArray(),
										   mesh.GetIndexBuffer(), shader));
	renderer.Flush();
}

} // namespace renderel::test
