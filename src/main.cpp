#include "Camera.hpp"
#include "GameEventHandler.hpp"
#include "InputControl.hpp"
#include "Transform.hpp"
#include "WindowGLFW.hpp"
#include "graphics/BasicRenderer.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/OBJLoader.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"
#include "math/Mat4.hpp"
#include "math/Quaternion.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "test/Test.hpp"
#include "test/TestClearColor.hpp"

using namespace renderel;
using namespace math;
using namespace graphics;

#define WIDTH 1080
#define HEIGHT 720

int main() {
	GameEventHandler gameEventHandler;
	InputControl horizontal;
	InputControl vertical;

	// FIXME: Going in the z direction causes model to disappear
	InputControl zdirection;

	InputControl rotationX;
	InputControl rotationY;
	InputControl rotationZ;

	gameEventHandler.AddKeyControl(GLFW_KEY_A, horizontal, -1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_D, horizontal, 1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_S, vertical, -1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_W, vertical, 1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_T, zdirection, -1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_Y, zdirection, 1.0f);

	gameEventHandler.AddKeyControl(GLFW_KEY_LEFT, horizontal, -1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_RIGHT, horizontal, 1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_DOWN, vertical, -1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_UP, vertical, 1.0f);

	gameEventHandler.AddKeyControl(GLFW_KEY_Q, rotationX, 1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_E, rotationX, -1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_Z, rotationY, 1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_X, rotationY, -1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_C, rotationZ, 1.0f);
	gameEventHandler.AddKeyControl(GLFW_KEY_V, rotationZ, -1.0f);

	Window *window =
		new WindowGLFW(WIDTH, HEIGHT, "Renderel", &gameEventHandler);

	Renderer<unsigned int>::InitGraphics();
	Renderer<unsigned int>::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	BasicRenderer<unsigned int> renderer;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 0
		0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, // 2
		-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, // 1
		0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // 3
		-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // 4
		0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, // 5
		-0.5f, 0.5f,  0.5f,  0.0f, 1.0f, // 6
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f  // 7
	};

	unsigned int indices[] = {
		// Back face
		0, 1, 2, //
		1, 2, 3, //
		// Front face
		4, 5, 6, //
		5, 6, 7, //
		// Left face
		0, 2, 4, //
		2, 4, 6, //
		// Right face
		1, 3, 5, //
		3, 5, 7, //
		// Top face
		2, 3, 6, //
		3, 6, 7, //
		// Bottom face
		0, 1, 4, //
		1, 4, 5  //
	};

	VertexArray *va = new VertexArray();

	VertexBuffer *vb = new VertexBuffer(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	va->AddBuffer(vb, layout);

	IndexBuffer<unsigned int> *ib = new IndexBuffer<unsigned int>(
		indices, sizeof(indices) / sizeof(indices[0]));

	VertexArray *va2 = nullptr;
	IndexBuffer<unsigned int> *ib2 = nullptr;

	if (!OBJLoader::Load<>("res/models/monkey.obj", ib2, va2)) {
		std::cerr << "Failed to load OBJ! file" << std::endl;
		return 1;
	}

	Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

	shader.Bind();

	Renderable<unsigned int> renderable2(va2, ib2, shader);

	float aspectRatio = 1.0f * WIDTH / HEIGHT;

	Texture texture("res/textures/bricks.jpg");

	float g = 0.0f;

	float xPos = 0.0f;
	float yPos = 0.0f;
	float zPos = 0.0f;

	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	Renderable<unsigned int> renderable(va, ib, shader);

	Camera camera(Vec3<>(0.0f, 0.0f, 0.0f), 70.0f,
				  static_cast<float>(window->GetHeight()) / window->GetWidth(),
				  0.01f, 10000.0f);

	float prevTime = 0;
	float newTime = static_cast<float>(glfwGetTime());
	float deltaTime;

	test::Test *currentTest = nullptr;
	test::TestMenu *testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear color test");

	const char *glsl_version = "#version 130";
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL((APIWindowHandleGLFW)window->GetAPIHandle(),
								 false);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	while (!window->ShouldClose()) {
		deltaTime = newTime - prevTime;
		prevTime = newTime;

		window->PollEvents();
		Renderer<>::Clear();

		Vec2<int> mousePos;
		gameEventHandler.GetMousePosition(mousePos);
		Vec2<> mousePosf =
			Vec2<>(map(mousePos.x, 0, WIDTH, -aspectRatio, aspectRatio),
				   map(mousePos.y, HEIGHT, 0, -1.0f, 1.0f));

		renderable.GetShader().SetUniform2f("u_LightPos", mousePosf.x,
											mousePosf.y);

		Mat4<> proj = Mat4<>::SimplePerspective(aspectRatio);
		// Mat4<> view = camera.GetView();
		renderable.GetShader().SetUniformMat4f("u_Proj", proj);
		// renderable.GetShader().SetUniformMat4f("u_View", view);
		float s = sinf(g);
		renderable.GetShader().SetUniform4f("u_Color", 0.5f + s / 3, 0.3f,
											0.5f + cosf(g) / 3, 1.0f);

		xPos += horizontal.GetAmount() * deltaTime;
		yPos += vertical.GetAmount() * deltaTime;
		zPos += zdirection.GetAmount() * deltaTime;

		camera.SetPosition(Vec3<>(xPos, yPos, zPos));

		xRot += rotationX.GetAmount() * deltaTime * 150;
		yRot += rotationY.GetAmount() * deltaTime * 150;
		zRot += rotationZ.GetAmount() * deltaTime * 150;

		Transform<> transform(Vec3<>(0.0f, 0.0f, -5.0f - zPos),
							  Quaternion<>(Vec3<>(1.0f, 0.0f, 0.0f), xRot) *
								  Quaternion<>(Vec3<>(0.0f, 1.0f, 0.0f), yRot) *
								  Quaternion<>(Vec3<>(0.0f, 0.0f, 1.0f), zRot),
							  Vec3<>(0.4f + s / 30));

		Mat4<> model = transform.GetModel();
		shader.SetUniformMat4f("u_Model", model);

		texture.Bind();
		shader.SetUniform1i("u_Sampler", 0);

		// renderer.Submit(renderable);
		renderer.Submit(renderable2);

		renderer.Flush();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest) {
			currentTest->OnUpdate(deltaTime);
			currentTest->OnRender();
			ImGui::Begin("Test");
			currentTest->OnGUIRender();

			if (currentTest != testMenu && ImGui::Button("| <-- |")) {
				delete currentTest;
				currentTest = testMenu;
			}

			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window->SwapBuffers();

		g += 0.005;
		newTime = static_cast<float>(glfwGetTime());
	}

	// TODO: delete currentTest;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
