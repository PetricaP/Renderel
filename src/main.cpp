#include "GameEventHandler.hpp"
#include "ImGUI.hpp"
#include "InputControl.hpp"
#include "Transform.hpp"
#include "WindowGLFW.hpp"
#include "core/Common.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/OBJLoader.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/EulerAngle.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include "test/TestCamera.hpp"
#include "test/TestClearColor.hpp"
#include "test/TestECS.hpp"
#include "test/TestFaceCulling.hpp"
#include "test/TestInput.hpp"
#include "test/TestMenu.hpp"
#include "test/TestOBJLoader.hpp"
#include "test/TestSkybox.hpp"
#include "test/TestTexturedCube.hpp"
#include "test/TestTriangleColor.hpp"
#include <imgui.h>
#include <memory>

using namespace renderel;

int32 main() {
	constexpr int32 WIDTH = 1080;
	constexpr int32 HEIGHT = 720;

	auto gameEventHandler = std::make_unique<GameEventHandler>();

	auto window = std::make_unique<WindowGLFW>(WIDTH, HEIGHT, "Renderel",
											   std::move(gameEventHandler));

	auto gui = std::make_unique<ImGUI>(window->GetAPIHandle(), "#version 130");

	window->SetGUI(std::move(gui));

	graphics::Renderer<>::InitGraphics();
	graphics::Renderer<>::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::unique_ptr<test::TestMenu> testMenu(new test::TestMenu(*window));

	testMenu->RegisterTest<test::TestClearColor>("Clear color test");
	testMenu->RegisterTest<test::TestTriangleColor>("Triangle color test");
	testMenu->RegisterTest<test::TestTexturedCube>("Textured cube test");
	testMenu->RegisterTest<test::TestOBJLoader>("Obj loader test");
	testMenu->RegisterTest<test::TestInput>("Input test");
	testMenu->RegisterTest<test::TestCamera>("Camera test");
	testMenu->RegisterTest<test::TestFaceCulling>("Face culling test");
	testMenu->RegisterTest<test::TestSkybox>("Skybox test");
	testMenu->RegisterTest<test::TestECS>("ECS test");

	float prevTime = 0;
	float newTime = static_cast<float>(glfwGetTime());
	float deltaTime;

	while (!window->ShouldClose()) {
		deltaTime = newTime - prevTime;
		prevTime = newTime;

		window->PollEvents();
		graphics::Renderer<>::Clear();

		testMenu->Run(deltaTime);

		window->GetGUI()->Render();

		window->SwapBuffers();

		newTime = static_cast<float>(glfwGetTime());
	}
}
