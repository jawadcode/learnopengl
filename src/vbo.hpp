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

    template <class Vertex> void init(std::span<const Vertex> vertices) {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                     vertices.data(), GL_STATIC_DRAW);
    }

    ~VBO();

    void bind() const;

    void unbind() const;
};
