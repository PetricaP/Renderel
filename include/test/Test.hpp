#pragma once

namespace renderel::test {

class Test {
  public:
	Test() = default;
	virtual ~Test() = default;

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnGUIRender() {}
};

} // namespace renderel::test
