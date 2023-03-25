#include "program.hpp"

#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const std::string read_file(const std::string &path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::string content{std::istreambuf_iterator<char>(file),
                        std::istreambuf_iterator<char>()};
    return content;
}

Program::Program(const std::string &vertex_path,
                 const std::string &fragment_path)
    : m_vertex_shader_id(glCreateShader(GL_VERTEX_SHADER)),
      m_fragment_shader_id(glCreateShader(GL_FRAGMENT_SHADER)),
      m_vertex_shader(read_file(vertex_path)),
      m_fragment_shader(read_file(fragment_path))

{
    
}

Program::~Program() {}