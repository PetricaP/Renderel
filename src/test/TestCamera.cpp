#include "test/TestCamera.hpp"
#include "GameEventHandler.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace renderel::test {

TestCamera::TestCamera(const std::shared_ptr<Window> window)
	: Test(window), m_Color(0.2f, 0.2f, 0.2f, 1.0f),

	  transform(math::Vec3<>(0.0f, 0.0f, 5.0f),
				math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), 0.0f),
				math::Vec3<>(1.0f)),

	  aspectRatio(static_cast<float>(window->GetWidth()) / window->GetHeight()),
	  position(math::Vec3<>(0.0f, 0.0f, -3.0f)),
	  camera(Camera(position, 70.0f, aspectRatio, 0.1f, 100.0f)) {

	GameEventHandler *handler =
		static_cast<GameEventHandler *>(window->GetEventHandler());

	handler->AddKeyControl(GLFW_KEY_W, yAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_S, yAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_D, xAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_A, xAxis, -1.0f);

	handler->AddKeyControl(GLFW_KEY_R, zAxis, 1.0f);
	handler->AddKeyControl(GLFW_KEY_F, zAxis, -1.0f);

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

	transform.SetPosition(math::Vec3<>(0.0f, 0.0f, 4.0f));
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
}

void TestCamera::OnUpdate(float deltaTime) {
	math::Mat4<> view = camera.GetView();
	shader->Bind();
	shader->SetUniformMat4f("u_View", view);

	position.x += xAxis.GetAmount() * deltaTime * 10.0f;
	position.y += yAxis.GetAmount() * deltaTime * 10.0f;
	position.z += zAxis.GetAmount() * deltaTime * 10.0f;

	camera.SetPosition(math::Vec3<>(position));
}

void TestCamera::OnGUIRender() {
	if (ImGui::Button("Reset to defaults")) {
		position = math::Vec3<>(0.0f, 0.0f, -3.0f);
	}
}

void TestCamera::OnRender() {
	graphics::Renderer<>::Clear();
	renderer->Submit(graphics::Renderable(va, ib, *shader));
	renderer->Flush();
}

} // namespace renderel::test
