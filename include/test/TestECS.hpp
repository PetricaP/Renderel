#ifndef TESTECS_HPP
#define TESTECS_HPP

#include "Camera.hpp"
#include "Test.hpp"
#include "Transform.hpp"
#include "ecs/ECS.hpp"
#include "graphics/Texture.hpp"

namespace renderel::test {

struct TransformComponent : public ECSComponent<TransformComponent> {
	Transform<> transform;
};

struct RenderableMeshComponent : public ECSComponent<RenderableMeshComponent> {
	graphics::VertexArray *va = nullptr;
	graphics::IndexBuffer *ib = nullptr;
};

struct CameraComponent : public ECSComponent<CameraComponent> {
	Camera camera;
};

class TestECS : public Test {
  private:
	ECS m_ECS;
	graphics::Shader shader;
	EntityHandle entity;
	TransformComponent transformComponent;
	RenderableMeshComponent renderableMeshComponent;
	CameraComponent cameraComponent;
	graphics::Texture texture;

	std::unique_ptr<graphics::VertexArray> m_VA;
	std::unique_ptr<graphics::IndexBuffer> m_IB;

  public:
	TestECS(const Window &window);
	~TestECS() override = default;
	void OnRender() override;
	void OnUpdate(float deltaTime) override;
	void OnGUIRender() override;
};

} // namespace renderel::test

#endif // TESTECS_HPP
