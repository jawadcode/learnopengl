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

void main() {
    gl_Position = vec4(pos, 1.0);
}
)";

const std::string FRAGMENT_SOURCE = R"(#version 330 core
out vec4 frag_colour;

uniform vec4 our_colour;

void main() {
    frag_colour = our_colour;
}
)";

int main() {
    Logger logger;
#define LOGGER logger

    Window window(logger, 800, 600, "LearnOpenGL");

    const std::array<glm::vec3, 3> vertices = {
        glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
        glm::vec3(-0.5f, -0.5f, 0.0f), // bottom left
        glm::vec3(0.0f, 0.5f, 0.0f),   // top
    };

    Program program(logger, VERTEX_SOURCE, FRAGMENT_SOURCE);
    program.link();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    VBO vbo;

    glBindVertexArray(vao);

    vbo.init<glm::vec3>(vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);

    glEnableVertexAttribArray(0);
    vbo.bind();

    while (!window.should_close()) {
        window.process_input();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.attach();

        auto time = glfwGetTime();
        auto red = cos(time) / 2.0 + 0.5;
        auto green = sin(time) / 2.0 + 0.5;
        auto blue = (red + green) / 2.0;
        auto vertex_colour_location =
            glGetUniformLocation(program.m_program_id, "our_colour");
        glUniform4f(vertex_colour_location, red, green, blue, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swap_buffers();
        glfwPollEvents();
    }
    LOG(LogLevel::Info, "Terminating GLFW");
    glfwTerminate();
    return 0;
}