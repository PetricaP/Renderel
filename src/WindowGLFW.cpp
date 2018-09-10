#include "WindowGLFW.hpp"
#include <iostream>

namespace renderel {

WindowGLFW::WindowGLFW(int width, int height, std::string title)
    : Window(width, height) {

    // TODO: Create logging system for errors
    if (!glfwInit()) {
        std::cerr << "Couldn't initialize glfw" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GLFWwindow =
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_GLFWwindow) {
        std::cerr << "Couldn't create glfw window." << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_GLFWwindow);
    glfwSwapInterval(1);
}

WindowGLFW::~WindowGLFW() {
    glfwDestroyWindow(m_GLFWwindow);
    glfwTerminate();
}

bool WindowGLFW::ShouldClose() const {
    return glfwWindowShouldClose(m_GLFWwindow);
}

void WindowGLFW::SwapBuffers() const { glfwSwapBuffers(m_GLFWwindow); }

void WindowGLFW::PollEvents() const { glfwPollEvents(); }

} // namespace renderel
