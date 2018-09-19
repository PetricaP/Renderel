#ifndef TESTSKYBOX_HPP
#define TESTSKYBOX_HPP

#include "Camera.hpp"
#include "GameEventHandler.hpp"
#include "graphics/Cubemap.hpp"
#include "math/EulerAngle.hpp"
#include "test/TestOBJLoader.hpp"

namespace renderel::test {

class TestSkybox : public TestOBJLoader {
  private:
	graphics::Cubemap *m_Cubemap;

	Camera m_Camera;

	static constexpr float defaultRotationSensitivity = 100000.0f;
	float rotationSensitivity = defaultRotationSensitivity;

	static constexpr float defaultMovementSensitivity = 10.0f;
	float movementSensitivity = defaultMovementSensitivity;

	math::EulerAngle<> eulerAngle;
	GameEventHandler *handler = nullptr;

	InputControl xAxis;
	InputControl yAxis;
	InputControl zAxis;
	InputControl xRotation;

  public:
	TestSkybox(const std::shared_ptr<Window> window);
	~TestSkybox();

	void OnRender() override;
	void OnGUIRender() override;
	void OnUpdate(float deltaTime) override;
};

} // namespace renderel::test

#endif // !TESTSKYBOX_HPP
