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
    VBO();
    
    template <class Vertex> void init(const std::span<Vertex> data) {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.size(), data.data(), GL_STATIC_DRAW);
    }

    ~VBO();

    void bind() const;

    void unbind() const;
};
