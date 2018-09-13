#include "WindowGLFW.hpp"
#include "EventHandler.hpp"
#include "GlobalGLFWEventHandler.hpp"
#include <iostream>
#include <queue>
#include <unordered_map>

namespace renderel {

// TODO: Methods practically the same, something is not right
// Consider using inheritance here
static void key_callback(GLFWwindow *window, int key, int, int action, int) {
    static int calls = 0;
    calls++;
    Event event;
    event.type = KEY;
    event.keyEvent.key = static_cast<unsigned int>(key);
    event.keyEvent.action = static_cast<unsigned int>(action);
    GlobalGLFWEventHandler::PushEvent(window, event);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int) {
    static int calls = 0;
    calls++;
    Event event;
    event.type = MOUSEBUTTON;
    event.mouseButtonEvent.button = static_cast<unsigned int>(button);
    event.mouseButtonEvent.action = static_cast<unsigned int>(action);
    GlobalGLFWEventHandler::PushEvent(window, event);
}

static void cursor_position_callback(GLFWwindow *window, double xPos,
                                     double yPos) {
    static int calls = 0;
    calls++;
    Event event;
    event.type = MOUSEMOTION;
    event.mouseMotionEvent.xPos = static_cast<int>(xPos);
    event.mouseMotionEvent.yPos = static_cast<int>(yPos);
    GlobalGLFWEventHandler::PushEvent(window, event);
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
    glfwSetMouseButtonCallback(m_GLFWwindow, mouse_button_callback);
    glfwSetCursorPosCallback(m_GLFWwindow, cursor_position_callback);

    GlobalGLFWEventHandler::GetEventPoll()[m_GLFWwindow].eventHandler =
        eventHandler;

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
    GlobalGLFWEventHandler::PollEvents(m_GLFWwindow);
}

} // namespace renderel
