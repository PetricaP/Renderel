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
#include "test/Test.hpp"
#include "test/TestCamera.hpp"
#include "test/TestClearColor.hpp"
#include "test/TestECS.hpp"
#include "test/TestFaceCulling.hpp"
#include "test/TestInput.hpp"
#include "test/TestOBJLoader.hpp"
#include "test/TestSkybox.hpp"
#include "test/TestTexturedCube.hpp"
#include "test/TestTriangleColor.hpp"
#include <imgui.h>
#include <memory>

using namespace renderel;

const int32 WIDTH = 1080;
const int32 HEIGHT = 720;

int32 main() {
	EventHandler *gameEventHandler = new GameEventHandler;

	std::shared_ptr<Window> window = std::make_shared<WindowGLFW>(
		WIDTH, HEIGHT, "Renderel", gameEventHandler, nullptr);

	GUI *gui = new ImGUI(window->GetAPIHandle(), "#version 130");
	window->SetGUI(gui);

	graphics::Renderer<uint32>::InitGraphics();
	graphics::Renderer<uint32>::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	std::shared_ptr<test::Test> currentTest = nullptr;
	std::shared_ptr<test::TestMenu> testMenu(
		new test::TestMenu(window, currentTest));
	currentTest = static_cast<std::shared_ptr<test::Test>>(testMenu);

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

		if (currentTest) {
			currentTest->OnUpdate(deltaTime);
			currentTest->OnRender();
			window->GetGUI()->Init();
			window->GetGUI()->Begin("Test");
			window->GetGUI()->Text("FPS: %.2f", 1.0f / deltaTime);
			currentTest->OnGUIRender();

			if (currentTest != testMenu) {
				if (window->GetGUI()->Button("| <-- |")) {
					currentTest = testMenu;
				}
			} else {
				if (window->GetGUI()->Button("Exit")) {
					window->Close();
				}
			}

			window->GetGUI()->End();
		}

		window->GetGUI()->Render();

		window->SwapBuffers();

		newTime = static_cast<float>(glfwGetTime());
	}
}
