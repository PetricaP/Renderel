#include "Debug.hpp"
#include "GL/glew.h"
#include "Window.hpp"
#include "graphics/Shader.hpp"
#include <iostream>

using namespace renderel::graphics;

int main() {
    Window window(960, 540, "Hello");
    window.SetClearColor(0.8f, 0.8f, 0.0f);

    float positions[] = {
        0.5f,  -0.5f, // 0
        0.0f,  0.5f,  // 1
        -0.5f, -0.5f  // 2
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    unsigned int vbo;
    GLCall(glGenBuffers(1, &vbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions,
                        GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));

    unsigned int indices[] = {0, 1, 2};

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                        GL_STATIC_DRAW));

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    shader.Bind();

    while (!window.ShouldClose()) {
        window.PollEvents();
        window.Clear();
        GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
        window.SwapBuffers();
    }
}
