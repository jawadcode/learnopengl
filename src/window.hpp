#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "src/logger.hpp"

using FrameBufSizeCB = void (*)(GLFWwindow *, GLint, GLint);
using KeyCB = void (*)(GLFWwindow *, GLint, GLint, GLint, GLint);

class Window {
  public:
    Window(const int width, const int height,
           const std::string &title = "GLFW Window", const int hint_major = 3,
           const int hint_minor = 3,
           const int hint_profile = GLFW_OPENGL_CORE_PROFILE);

    void set_framebuf_size_callback(FrameBufSizeCB cb);

    void set_key_callback(KeyCB cb);

    void load_gl_loader();

    void dump_gpu_info();

    inline bool is_open() { return !glfwWindowShouldClose(m_window); }

    inline void swap_bufs() { glfwSwapBuffers(m_window); }

    ~Window();

  private:
    GLFWwindow *m_window;
};
