#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

int main() {
	GLFWwindow* window = nullptr;

	if (!glfwInit()) {
		std::cerr << "Couldn't initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(960, 540, "Ceaw, kf?", NULL, NULL);
	if (!window)
	{
		std::cerr << "Couldn't create glfw window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK) {
		std::cerr << "Error!" << std::endl;
	}
	
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0F, 0.15F, 0.85F, 1.0F);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}
