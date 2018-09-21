#include "test/TestFaceCulling.hpp"

#include "Debug.hpp"
#include "graphics/OBJLoader.hpp"
#include <GL/glew.h>

namespace renderel::test {

TestFaceCulling::TestFaceCulling(const Window &window)
	: Test(window), rotation(30.0f, 0.0f, 0.0f),
	  texture("res/textures/UV_grid.png", graphics::Texture::TEXTURE_2D),
	  shader("shaders/vertexShader.glsl", "shaders/fragmentShaderTexture.glsl"),
	  transform(
		  math::Vec3<>(0.0f, 0.0f, -2.0f),
		  math::Quaternion<>(math::Vec3<>(1.0f, 0.0f, 0.0f), rotation.x) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 1.0f, 0.0f), rotation.y) *
			  math::Quaternion<>(math::Vec3<>(0.0f, 0.0f, 1.0f), rotation.z),
		  math::Vec3<>(1.0f)) {

	graphics::OBJLoader::Load<>("res/models/flipped_cube.obj", ib, va);

	shader.Bind();

	texture.Bind();
	shader.SetUniform1i("u_Sampler", 0);

	math::Mat4<> model = transform.GetModel();
	shader.SetUniformMat4f("u_Model", model);

	GLCall(glEnable(GL_CULL_FACE));
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

TestFaceCulling::~TestFaceCulling() { GLCall(glDisable(GL_CULL_FACE)); }

void TestFaceCulling::OnRender() {
	graphics::Renderer<>::Clear();
	renderer.Submit(graphics::Renderable(va.get(), ib.get(), shader));
	renderer.Flush();
}

void TestFaceCulling::OnGUIRender() {}

void TestFaceCulling::OnUpdate(float deltaTime) {
	float aspectRatio = 1.0f * m_Window.GetWidth() / m_Window.GetHeight();
	math::Mat4<> proj =
		math::Mat4<>::Perspective(70.0f, aspectRatio, 0.1f, 40.0f);
	shader.SetUniformMat4f("u_Proj", proj);

	rotation.y += deltaTime * 50.0f;

	transform.SetRotation(rotation);

	math::Mat4<> model = transform.GetModel();
	shader.SetUniformMat4f("u_Model", model);
}

} // namespace renderel::test
