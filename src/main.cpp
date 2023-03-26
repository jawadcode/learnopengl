#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <span>
#include <array>
#include "window.hpp"
#include "logger.hpp"
#include "vbo.hpp"
#include "index_buffer.hpp"

int main() {
    Logger logger;

    Window window(logger, 800, 600, "LearnOpenGL");

    // clang-format off
    auto vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };
    // clang-format on

    VBO vbo(std::span{vertices});

    //TOOD: Figure out wtf VAOs are and create a class that works nicely with
    // the VBO one, as well as provides meaningful abstractions

    while (!window.should_close()) {
        window.process_input();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swap_buffers();
        glfwPollEvents();
    }
    return 0;
}