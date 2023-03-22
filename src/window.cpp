#include "window.hpp"
#include "GLFW/glfw3.h"
#include "src/logger.hpp"

#define LOGGER m_logger

Window::Window(Logger &logger, GLint width, GLint height,
               const std::string &title)
    : m_logger(logger) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_raw_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (m_raw_window == NULL) {
        LOG(LogLevel::Fatal, "Failed to create GLFW window\n");
        glfwTerminate();
        std::exit(1);
    }
    glfwMakeContextCurrent(m_raw_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG(LogLevel::Fatal, "Failed to initialize GLAD");
        std::exit(1);
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(
        m_raw_window, [](GLFWwindow *window, GLint width, GLint height) {
            glViewport(0, 0, width, height);
        });
    LOG(LogLevel::Info, "GLFW window initialized");
}

void Window::process_input() {
    if (glfwGetKey(m_raw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_raw_window, true);
        LOG(LogLevel::Info, "Window Closed");
    }
}

bool Window::should_close() { return glfwWindowShouldClose(m_raw_window); }

void Window::swap_buffers() { glfwSwapBuffers(m_raw_window); }