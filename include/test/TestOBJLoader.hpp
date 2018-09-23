#ifndef TESTOBJLOADER_HPP
#define TESTOBJLOADER_HPP

#include "Transform.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/Texture.hpp"
#include "math/Vec4.hpp"
#include "test/Test.hpp"

namespace renderel::test {

class TestOBJLoader : public Test {
  protected:
	math::Vec4<> m_Color;

	graphics::Mesh<> *mesh;
	graphics::Renderer<> *renderer;
	graphics::Shader *shader;
	graphics::Texture *texture;

	math::Vec3<> rotation;
	Transform<> transform;

	math::Mat4<> model;
	math::Mat4<> proj;

  public:
	TestOBJLoader(
		const std::shared_ptr<Window> window,
		const std::string objPath = "res/models/monkey.obj",
		const std::string texturePath = "res/textures/monkey_baked.png",
		const std::string vertexShaderPath = "shaders/vertexShader.glsl",
		const std::string fragmentShaderPath =
			"shaders/fragmentShaderTexture.glsl",
		const bool loadTextures = true, const bool loadNormals = false);
	~TestOBJLoader() override;
	void OnRender() override;
	void OnGUIRender() override;
	void OnUpdate(float) override;
};

} // namespace renderel::test

#endif // TESTOBJLOADER_HPP
