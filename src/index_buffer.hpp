#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <span>

#pragma once

class IndexBuffer {
  private:
    GLuint m_index_buffer_id;
    std::size_t m_count;

  public:
    IndexBuffer(const std::span<GLuint> indices);

    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;
};
