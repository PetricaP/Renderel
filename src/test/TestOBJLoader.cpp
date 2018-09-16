#include "test/TestOBJLoader.hpp"
#include "graphics/OBJLoader.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"
#include <imgui.h>

#define WIDTH 1080
#define HEIGHT 720

namespace renderel::test {

TestOBJLoader::TestOBJLoader()
	: m_Color{0.1f, 0.1f, 0.1f, 0.5f}, rotation(0.0f, 0.0f, 0.0f),
	  transform(
		  math::Vec3<>(0.0f, 0.0f, -5.0f),
		  math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), rotation.x) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 1.0f, 0.0f), rotation.y) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 0.0f, 1.0f), rotation.z),
		  math::Vec3<>(1.0f)) {

	graphics::OBJLoader::Load<>("res/models/monkey.obj", ib, va);

	renderer = new graphics::BasicRenderer();
	shader = new graphics::Shader("shaders/vertexShader.glsl",
								  "shaders/fragmentShaderTexture.glsl");

	shader->Bind();

	texture = new graphics::Texture("res/textures/monkey_baked.png");
	texture->Bind();
	shader->SetUniform1i("u_Sampler", 0);

	math::Mat4<> model = transform.GetModel();
	shader->SetUniformMat4f("u_Model", model);

	float aspectRatio = 1.0f * WIDTH / HEIGHT;
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 40.0f);
	shader->SetUniformMat4f("u_Proj", proj);
}

TestOBJLoader::~TestOBJLoader() {
	delete shader;
	delete va;
	delete ib;
	delete renderer;
}

void TestOBJLoader::OnUpdate(float) {

	g += 0.01f;

	math::Quaternion<> qX(math::Vec3<>(1.0f, 0.0f, 0.0f), rotation.x);
	math::Quaternion<> qY(math::Vec3<>(0.0f, 1.0f, 0.0f), rotation.y);
	math::Quaternion<> qZ(math::Vec3<>(0.0f, 0.0f, 1.0f), rotation.z);

	transform.SetRotation(qX * qY * qZ);

	math::Mat4<> model = transform.GetModel();
	shader->SetUniformMat4f("u_Model", model);

	shader->SetUniform4f("u_Color", 0.5f + sinf(g) / 2.0f,
						 0.5f + cosf(g) / 2.0f, 1.0f, 0.5f);
}

void TestOBJLoader::OnGUIRender() {
	ImGui::SliderFloat3("Position", &transform.GetPosition().x, -50.0f, 5.0f);
	ImGui::SliderFloat3("Rotation", &rotation.x, -180.0f, 180.0f);
	ImGui::SliderFloat3("Scale", &transform.GetScale().x, 0.0f, 10.0f);

	if (ImGui::Button("Reset to defaults")) {
		transform.SetPosition(math::Vec3<>(0.0f, 0.0f, -5.0f));
		rotation.x = 0;
		rotation.y = 0;
		rotation.z = 0;
		transform.SetScale(math::Vec3<>(1.0f));
	}
}

void TestOBJLoader::OnRender() {

	graphics::Renderer<>::Clear();
	renderer->Submit(graphics::Renderable(va, ib, *shader));
	renderer->Flush();
}

} // namespace renderel::test
