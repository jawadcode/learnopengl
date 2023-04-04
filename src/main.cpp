#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <span>
#include <array>
#include <vector>
#include "window.hpp"
#include "logger.hpp"
#include "program.hpp"
#include "vbo.hpp"
#include "index_buffer.hpp"

const std::string VERTEX_SOURCE = R"(#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

uniform float timer;
out vec3 our_colour;

void main() {
    mat3 rotation = mat3(cos(timer), -sin(timer), 0.0,
                         sin(timer),  cos(timer), 0.0,
                         0.0,         0.0,        1.0);
    gl_Position = vec4(rotation * pos, 1.0);
    our_colour = colour;
}
)";

const std::string FRAGMENT_SOURCE = R"(#version 330 core
out vec4 frag_colour;
in vec3 our_colour;

void main() {
    frag_colour = vec4(our_colour, 1.0);
}
)";

int main() {
    Logger logger;
#define LOGGER logger

    Window window(logger, 500, 500, "LearnOpenGL");

    // clang-format off
    const std::array<glm::vec3, 6> vertices = {
        // position:                             colour:
        glm::vec3(-std::sqrt(3)/2, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), // bottom right
        glm::vec3( std::sqrt(3)/2, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), // bottom left
        glm::vec3( 0.0f,            1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), // top
    };
    // clang-format on

    Program program(logger, VERTEX_SOURCE, FRAGMENT_SOURCE);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    VBO vbo;

    glBindVertexArray(vao);

    vbo.init<glm::vec3>(vertices);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3),
                          (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3),
                          (GLvoid *)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    vbo.bind();

    while (!window.should_close()) {
        window.process_input();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.attach();
        program.set_uniform("timer", (GLfloat)glfwGetTime());
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swap_buffers();
        glfwPollEvents();
    }
    LOG(LogLevel::Info, "Terminating GLFW");
    glfwTerminate();
    return 0;
}