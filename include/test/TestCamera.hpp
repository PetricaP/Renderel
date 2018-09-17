#ifndef TESTCAMERA_HPP
#define TESTCAMERA_HPP

#include "Camera.hpp"
#include "InputControl.hpp"
#include "Transform.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/Texture.hpp"
#include "math/Vec4.hpp"
#include "test/Test.hpp"

namespace renderel::test {

class TestCamera : public Test {
  private:
	math::Vec4<> m_Color;

	static constexpr float size = 0.5f;
	static constexpr float m_Vertices[] = {
		// clang-format off
		// Back face
		-size, -size, -size, 0.0f, 0.0f, // 0
		 size, -size, -size, 1.0f, 0.0f, // 2
		-size,  size, -size, 0.0f, 1.0f, // 1
		 size,  size, -size, 1.0f, 1.0f, // 3
		// Front face
		-size, -size,  size, 0.0f, 0.0f, // 4
		 size, -size,  size, 1.0f, 0.0f, // 5
		-size,  size,  size, 0.0f, 1.0f, // 6
		 size,  size,  size, 1.0f, 1.0f,  // 7
		// Left face
		-size, -size, -size, 0.0f, 0.0f, // 8
		-size, -size,  size, 1.0f, 0.0f, // 9
		-size,  size, -size, 0.0f, 1.0f, // 10
		-size,  size,  size, 1.0f, 1.0f, // 11
		// Right face
		 size, -size, -size, 0.0f, 0.0f, // 12
		 size, -size,  size, 1.0f, 0.0f, // 13
		 size,  size, -size, 0.0f, 1.0f, // 14
		 size,  size,  size, 1.0f, 1.0f, // 15
		// Top face
		-size,  size, -size, 0.0f, 0.0f, // 16
		 size,  size, -size, 1.0f, 0.0f, // 17
		-size,  size,  size, 0.0f, 1.0f, // 18
		 size,  size,  size, 1.0f, 1.0f, // 19
		// Left face
		-size, -size, -size, 0.0f, 0.0f, // 20
		 size, -size, -size, 1.0f, 0.0f, // 21
		-size, -size,  size, 0.0f, 1.0f, // 22
		 size, -size,  size, 1.0f, 1.0f, // 23
		// clang-format on
	};

	static constexpr unsigned int indices[] = {
		// Back face
		0, 1, 2, //
		1, 2, 3, //
		// Front face
		4, 5, 6, //
		5, 6, 7, //
		// Left face
		8, 9, 10,  //
		9, 10, 11, //
		// Right face
		12, 13, 14, //
		13, 14, 15, //
		// Top face
		16, 17, 18, //
		17, 18, 19, //
		// Bottom face
		20, 21, 22, //
		21, 22, 23  //
	};

	InputControl xAxis;
	InputControl yAxis;
	InputControl zAxis;
	InputControl xRotation;

	graphics::VertexArray *va = nullptr;
	graphics::VertexBuffer *vb = nullptr;
	graphics::IndexBuffer<> *ib = nullptr;
	graphics::Renderer<> *renderer = nullptr;
	graphics::Shader *shader = nullptr;
	graphics::Texture *texture = nullptr;

	math::Vec3<> position;
	Transform<> transform;
	float aspectRatio;
	Camera camera;

	math::Mat4<> model;
	math::Mat4<> proj;

  public:
	TestCamera(const std::shared_ptr<Window> window);
	~TestCamera() override;
	void OnRender() override;
	void OnGUIRender() override;
	void OnUpdate(float) override;
};

} // namespace renderel::test

#endif // TESTCAMERA_HPP
