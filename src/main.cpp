#include "Debug.hpp"
#include "GL/glew.h"
#include "Window.hpp"
#include "graphics/Shader.hpp"
#include "graphics/VertexBuffer.hpp"
#include "graphics/VertexArray.hpp"
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

    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);
    va.Bind();

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
