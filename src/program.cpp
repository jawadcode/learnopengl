#include "program.hpp"

#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.hpp"

#define MAX_INFO_LOG_LEN 512
#define LOGGER logger

const std::string read_file(const std::string &path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::string content{std::istreambuf_iterator<char>(file),
                        std::istreambuf_iterator<char>()};
    return content;
}

void check_shader_compilation(GLuint shader_id, bool is_vertex,
                              Logger &logger) {
    int success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info_log[MAX_INFO_LOG_LEN];
        glGetShaderInfoLog(shader_id, MAX_INFO_LOG_LEN, NULL, info_log);
        const std::string shader_type = is_vertex ? "vertex" : "fragment";
        LOG(LogLevel::Fatal, "Failed to compile {} shader: {}", shader_type,
            info_log);
        std::exit(1);
    }
}

Program::Program(Logger &logger, const std::string &vertex_source,
                 const std::string &fragment_source)
    : logger(logger) {
    m_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_source_cstr = vertex_source.c_str();
    //    LOG(LogLevel::Debug, "Vertex Shader: {}", vertex_source_cstr);
    glShaderSource(m_vertex_shader_id, 1, &vertex_source_cstr, NULL);
    glCompileShader(m_vertex_shader_id);
    check_shader_compilation(m_vertex_shader_id, true, logger);

    m_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_source_cstr = fragment_source.c_str();
    //    LOG(LogLevel::Debug, "Fragment Shader: {}", fragment_source_cstr);
    glShaderSource(m_fragment_shader_id, 1, &fragment_source_cstr, NULL);
    glCompileShader(m_fragment_shader_id);
    check_shader_compilation(m_fragment_shader_id, false, logger);
}

Program::~Program() {
    glDeleteShader(m_vertex_shader_id);
    glDeleteShader(m_fragment_shader_id);
}

void Program::link() {
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, m_vertex_shader_id);
    glAttachShader(m_program_id, m_fragment_shader_id);
    glLinkProgram(m_program_id);

    int success;
    glGetProgramiv(m_vertex_shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[MAX_INFO_LOG_LEN];
        glGetProgramInfoLog(m_program_id, 512, NULL, info_log);
        std::cout << info_log << std::endl;
        LOG(LogLevel::Fatal, "Failed to link shaders: {}", info_log);
        std::exit(1);
    }

    glDeleteShader(m_vertex_shader_id);
    glDeleteShader(m_fragment_shader_id);
}

void Program::attach() { glUseProgram(m_program_id); }
