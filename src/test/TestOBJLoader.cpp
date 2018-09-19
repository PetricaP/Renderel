#include "test/TestOBJLoader.hpp"
#include "graphics/OBJLoader.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"
#include <imgui.h>

namespace renderel::test {

TestOBJLoader::TestOBJLoader(const std::shared_ptr<Window> window,
							 const std::string objPath,
							 const std::string texturePath,
							 const std::string vertexShaderPath,
							 const std::string fragmentShaderPath)
	: Test(window), m_Color{0.1f, 0.1f, 0.1f, 0.5f}, rotation(0.0f, 0.0f, 0.0f),
	  transform(
		  math::Vec3<>(0.0f, 0.0f, -2.5f),
		  math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), rotation.x) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 1.0f, 0.0f), rotation.y) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 0.0f, 1.0f), rotation.z),
		  math::Vec3<>(1.0f)) {

	mesh = new graphics::Mesh<>(objPath.c_str());

	renderer = new graphics::BasicRenderer();
	shader = new graphics::Shader(vertexShaderPath.c_str(),
								  fragmentShaderPath.c_str());

	shader->Bind();

	texture = new graphics::Texture(texturePath.c_str());
	texture->Bind();
	shader->SetUniform1i("u_Sampler", 0);

	math::Mat4<> model = transform.GetModel();
	shader->SetUniformMat4f("u_Model", model);
}

TestOBJLoader::~TestOBJLoader() {
	delete shader;
	delete mesh;
	delete renderer;
}

void TestOBJLoader::OnUpdate(float) {

	float aspectRatio = 1.0f * m_Window->GetWidth() / m_Window->GetHeight();
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 40.0f);
	shader->SetUniformMat4f("u_Proj", proj);

	transform.SetRotation(rotation);

	math::Mat4<> model = transform.GetModel();
	shader->SetUniformMat4f("u_Model", model);
}

void TestOBJLoader::OnGUIRender() {
	ImGui::SliderFloat3("Position", &transform.GetPosition().x, -50.0f, 5.0f);
	ImGui::SliderFloat3("Rotation", &rotation.x, -180.0f, 180.0f);
	ImGui::SliderFloat3("Scale", &transform.GetScale().x, 0.0f, 10.0f);

	if (ImGui::Button("Reset to defaults")) {
		transform.SetPosition(math::Vec3<>(0.0f, 0.0f, -2.5f));
		rotation.x = 0;
		rotation.y = 0;
		rotation.z = 0;
		transform.SetScale(math::Vec3<>(1.0f));
	}
}

void TestOBJLoader::OnRender() {

	// graphics::Renderer<>::Clear();
	renderer->Submit(graphics::Renderable(*mesh, *shader));
	renderer->Flush();
}

} // namespace renderel::test
