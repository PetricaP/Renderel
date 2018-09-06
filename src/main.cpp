#include "Debug.hpp"
#include "GL/glew.h"
#include "Window.hpp"
#include <iostream>

static int CompileShader(char shaderSource[], unsigned int type) {
    GLCall(unsigned int shaderID = glCreateShader(type));
    GLCall(glShaderSource(shaderID, 1, &shaderSource, NULL));

    GLCall(glCompileShader(shaderID));

    int compilationResult = 0;
    GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult));
    if (compilationResult != GL_TRUE) {
        fprintf(stderr, "Failed to compile %s shader.\n",
                (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
        int infoLogLength = 0;
        GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));
        char log[1024];
        GLCall(glGetShaderInfoLog(shaderID, infoLogLength, NULL, log));
        fprintf(stderr, "Log: %s\n", log);
        GLCall(glDeleteShader(shaderID));
    }

    return shaderID;
}

static unsigned int CreateGLSLProgram(unsigned int vertexShaderID,
                                      unsigned int fragmentShaderID) {
    GLCall(unsigned int shaderID = glCreateProgram());
    GLCall(glAttachShader(shaderID, vertexShaderID));
    GLCall(glAttachShader(shaderID, fragmentShaderID));
    GLCall(glLinkProgram(shaderID));

    int result;
    GLCall(glGetProgramiv(shaderID, GL_LINK_STATUS, &result));
    if (result == GL_FALSE) {
        fprintf(stderr, "Failed to link program\n");
        return 0;
    }

    int infoLogLength;
    GLCall(glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));
    if (infoLogLength > 0) {
        char *log = (char *)malloc((infoLogLength + 1) * sizeof(char));
        if (log == NULL) {
            fprintf(stderr, "Couldn't allocate memory for shader log.");
            exit(EXIT_FAILURE);
        }
        GLCall(glGetProgramInfoLog(shaderID, infoLogLength, NULL, log));
        fprintf(stderr, "Log: %s\n", log);
        free(log);
    }

    GLCall(glDetachShader(shaderID, vertexShaderID));
    GLCall(glDetachShader(shaderID, fragmentShaderID));
    GLCall(glDeleteShader(vertexShaderID));
    GLCall(glDeleteShader(fragmentShaderID));
    GLCall(glUseProgram(shaderID));

    return shaderID;
}

int main() {
    renderel::graphics::Window window(960, 540, "Hello");
    window.setClearColor(0.7f, 0.7f, 0.2f);

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

    char vertexShaderSource[] = "#version 330 core\n"
                                "\n"
                                "layout(location = 0) in vec2 position;\n"
                                "\n"
                                "void main() {\n"
                                "   gl_Position = vec4(position, 0.0f, 1.0f);\n"
                                "}\n";

    char fragmentShaderSource[] = "#version 330 core\n"
                                  "\n"
                                  "layout(location = 0) out vec4 color;\n"
                                  "\n"
                                  "void main() {"
                                  "   color = vec4(0.5f, 0.1f, 0.1f, 1.0f);\n"
                                  "}\n";

    unsigned int vertexShaderID =
        CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShaderID =
        CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    unsigned int program = CreateGLSLProgram(vertexShaderID, fragmentShaderID);

    GLCall(glUseProgram(program));

    while (!window.ShouldClose()) {
        window.PollEvents();
        window.Clear();
        GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
        window.SwapBuffers();
    }
}
