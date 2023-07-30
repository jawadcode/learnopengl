#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <fmt/printf.h>
#include <optional>

#include "logger.hpp"
#include "src/utils.hpp"
#include "window.hpp"

#define LOGLEVEL_INFO

int main() {
    auto log_path = get_env("LOG_PATH");
    if (log_path != std::nullopt) {
        INIT_LOG(log_path.value());
    }

    const int width = 800;
    const int height = 600;

    Window window(width, height, "LearnOpenGL");

    window.set_framebuf_size_callback(
        [](GLFWwindow *window, GLint width, GLint height) {
            (void)window;
            glViewport(0, 0, width, height);
        });
    window.set_key_callback([](GLFWwindow *window, int key, int scancode,
                               int action, int modifiers) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            (void)window, (void)scancode, (void)modifiers;
            glfwSetWindowShouldClose(window, true);
            LOG_INFO("ESC pressed, window close event triggered");
        }
    });

    window.load_gl_loader();
    window.dump_gpu_info();

    while (window.is_open()) {
        // process input ig

        glClearColor(02.f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swap_bufs();
        glfwPollEvents();
    }

    return 0;
}