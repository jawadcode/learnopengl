#include "program.hpp"

#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.hpp"

#define MAX_INFO_LOG_LEN 1024
#define LOGGER logger

const std::string read_file(const std::string &path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::string content{std::istreambuf_iterator<char>(file),
                        std::istreambuf_iterator<char>()};
    return content;
}

Program::Program(Logger &logger, const std::string &vertex_source,
                 const std::string &fragment_source)
    : logger(logger) {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_source_cstr = vertex_source.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_source_cstr, NULL);
    glCompileShader(vertex_shader_id);

    GLint success;
    GLchar info_log[MAX_INFO_LOG_LEN];
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader_id, MAX_INFO_LOG_LEN, nullptr,
                           info_log);
        LOG(LogLevel::Fatal, "Failed to compile vertex shader: '{}'", info_log);
        std::exit(1);
    }

    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_source_cstr = fragment_source.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_source_cstr, NULL);
    glCompileShader(fragment_shader_id);

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader_id, MAX_INFO_LOG_LEN, nullptr,
                           info_log);
        LOG(LogLevel::Fatal, "Failed to compile fragment shader: '{}'",
            info_log);
        std::exit(1);
    }

    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader_id);
    glAttachShader(m_program_id, fragment_shader_id);
    glLinkProgram(m_program_id);

    glGetProgramiv(vertex_shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program_id, MAX_INFO_LOG_LEN, nullptr, info_log);
        std::cout << info_log << std::endl;
        LOG(LogLevel::Fatal, "Failed to link shaders: {}", info_log);
        std::exit(1);
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(vertex_shader_id);
}

Program::~Program() { glDeleteProgram(m_program_id); }

void Program::use() { glUseProgram(m_program_id); }

void Program::set_uniform(const std::string &name, GLboolean uniform) const {
    glUniform1i(glGetUniformLocation(m_program_id, name.c_str()),
                (GLint)uniform);
}

void Program::set_uniform(const std::string &name, GLint uniform) const {
    glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), uniform);
}

void Program::set_uniform(const std::string &name, GLfloat uniform) const {
    glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), uniform);
}
