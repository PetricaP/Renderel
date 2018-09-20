#ifndef TESTECS_HPP
#define TESTECS_HPP

#include "Test.hpp"
#include "Transform.hpp"
#include "ecs/ECS.hpp"

namespace renderel::test {

struct TransformComponent : public ECSComponent<TransformComponent> {
	Transform<> transform;
};

class TestECS : public Test {
  private:
	ECS m_ECS;
	Transform<> *workingTransform = nullptr;

  public:
	TestECS(std::shared_ptr<Window> window);
	~TestECS() override = default;
	void OnRender() override;
	void OnUpdate(float deltaTime) override;
	void OnGUIRender() override;
};

} // namespace renderel::test

#endif // TESTECS_HPP
