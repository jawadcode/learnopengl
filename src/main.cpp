#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <span>
#include <array>
#include "window.hpp"
#include "logger.hpp"
#include "program.hpp"
#include "vbo.hpp"
#include "index_buffer.hpp"

const std::string VERTEX_SOURCE = R"(#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const std::string FRAGMENT_SOURCE = R"(#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

int main() {
    Logger logger;
#define LOGGER logger

    Window window(logger, 800, 600, "LearnOpenGL");

    // clang-format off
    auto vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };
    // clang-format on

    Program program(logger, VERTEX_SOURCE, FRAGMENT_SOURCE);
    program.link();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    VBO vbo;
    glBindVertexArray(vao);
    vbo.init(std::span{vertices});
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);
    vbo.unbind();
    glBindVertexArray(0);

    while (!window.should_close()) {
        window.process_input();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.attach();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swap_buffers();
        glfwPollEvents();
    }
    LOG(LogLevel::Info, "Terminating GLFW");
    glfwTerminate();
    return 0;
}