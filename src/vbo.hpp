#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>

#pragma once

class VBO {
  private:
    GLuint m_vbo_id;

  public:
    template <class Vertex> VBO(const Vertex data[], std::size_t size) {
        glGenBuffers(1, &m_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    ~VBO();
    void Bind();
    void Unbind();
};
