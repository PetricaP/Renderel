#ifndef TESTECS_HPP
#define TESTECS_HPP

#include "Test.hpp"
#include "Transform.hpp"
#include "ecs/ECS.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/Mesh.hpp"

namespace renderel::test {

struct TransformComponent : public ECSComponent<TransformComponent> {
	Transform<> transform;
};

struct RenderableMeshComponent : public ECSComponent<RenderableMeshComponent> {
	graphics::Mesh<> mesh;
};

class TestECS : public Test {
  private:
	ECS m_ECS;
	Transform<> *workingTransform = nullptr;
	graphics::Shader shader;
	EntityHandle entity;
	graphics::BasicRenderer<> renderer;

  public:
	TestECS(const Window &window);
	~TestECS() override = default;
	void OnRender() override;
	void OnUpdate(float deltaTime) override;
	void OnGUIRender() override;
};

} // namespace renderel::test

#endif // TESTECS_HPP
