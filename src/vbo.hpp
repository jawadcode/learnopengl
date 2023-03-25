#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <span>

#pragma once

class VBO {
  private:
    GLuint m_vbo_id;

  public:
    template <class Vertex> VBO(const std::span<Vertex> data) {
        glGenBuffers(1, &m_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, data.size(), data.data(), GL_STATIC_DRAW);
    }
  
    ~VBO();
  
    void bind() const;
  
    void Unbind() const;
};
