#include <cstdlib>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "src/logger.hpp"
#include <iostream>
#include <string>

#pragma once

struct Window {
  private:
    GLFWwindow *m_raw_window;
    Logger &m_logger;

  public:
    Window(Logger &logger, GLint width, GLint height, const std::string &title);

    void process_input();

    bool should_close();

    void swap_buffers();

    ~Window() { glfwTerminate(); }
};