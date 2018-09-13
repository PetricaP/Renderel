#include "WindowGLFW.hpp"
#include "EventHandler.hpp"
#include "GlobalGLFWEventHandler.hpp"
#include <iostream>
#include <queue>
#include <unordered_map>

namespace renderel {

static GlobalGLFWEventHandler globalEventHandler;

void key_callback(GLFWwindow *window, int key, int, int action, int) {
    static int calls = 0;
    calls++;
    std::cout << "callback: " << calls << std::endl;
    Event event;
    event.key = static_cast<unsigned int>(key);
    event.action = static_cast<unsigned int>(action);
    globalEventHandler.PushEvent(window, event);
}

// TODO: Add mouse input management
WindowGLFW::WindowGLFW(int width, int height, std::string title,
                       EventHandler *eventHandler)
    : Window(width, height, eventHandler) {

    // TODO: Create logging system for errors
    if (!glfwInit()) {
        std::cerr << "Couldn't initialize glfw" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // TODO: implement flags for glfw window
    m_GLFWwindow =
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_GLFWwindow) {
        std::cerr << "Couldn't create glfw window." << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwSetKeyCallback(m_GLFWwindow, key_callback);

    globalEventHandler.GetEventPoll()[m_GLFWwindow].eventHandler = eventHandler;

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

void WindowGLFW::PollEvents() const {
    glfwPollEvents();
    globalEventHandler.PollEvents(m_GLFWwindow);
}

} // namespace renderel
