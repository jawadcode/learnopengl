#include "window.hpp"

Window::Window(const int width, const int height, const std::string &title,
               const int hint_major, const int hint_minor,
               const int hint_profile) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hint_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hint_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, hint_profile);

    std::string profile = hint_profile == GLFW_OPENGL_CORE_PROFILE ? "core"
                          : hint_profile == GLFW_OPENGL_COMPAT_PROFILE
                              ? "compatibility"
                              : "any";
    LOG_INFO("Initialised GLFW window (with hints: OpenGL {} profile, "
             "version {}.{})",
             profile, hint_major, hint_minor);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (m_window == nullptr) {
        LOG_FATAL("Failed to create GLFW window");
        glfwTerminate();
        std::exit(1);
    }
    glfwMakeContextCurrent(m_window);
    LOG_INFO("Created GLFW window and OpenGL context");
}

void Window::set_framebuf_size_callback(FrameBufSizeCB cb) {
    glfwSetFramebufferSizeCallback(m_window, cb);
}

void Window::set_key_callback(KeyCB cb) { glfwSetKeyCallback(m_window, cb); }

void Window::load_gl_loader() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_FATAL("Failed to initialize GLAD");
        std::exit(1);
    }
    LOG_INFO("GLAD GL loader loaded");
}

void Window::dump_gpu_info() {
    auto vendor = (const char *)glGetString(GL_VENDOR);
    auto renderer = (const char *)glGetString(GL_RENDERER);
    LOG_DEBUG("GPU Info - Vendor: {}, Renderer: {}", vendor, renderer);
}

Window::~Window() {
    LOG_INFO("GLFW window closed, terminating");
    glfwTerminate();
    m_window = nullptr;
}
