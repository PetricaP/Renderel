#include "Window.hpp"
#include <iostream>

namespace renderel::graphics {

Window::Window(int width, int height, std::string title)
    : m_Width(width), m_Height(height) {

    // TODO: Create logging system for errors
    if (!glfwInit()) {
        std::cerr << "Couldn't initialize glfw" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GLFWwindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_GLFWwindow) {
        std::cerr << "Couldn't create glfw window." << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_GLFWwindow);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Error!" << std::endl;
        exit(1);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Window::SetClearColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
}

Window::~Window() {
    glfwDestroyWindow(m_GLFWwindow);
    glfwTerminate();
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_GLFWwindow); }

void Window::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(m_GLFWwindow);
}

void Window::PollEvents() const {
    glfwPollEvents();
}

} // namespace renderel::graphics
