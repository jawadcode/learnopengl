#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <span>

#pragma once

class IndexBuffer {
  private:
    GLuint m_index_buffer_id;

  public:
    IndexBuffer();

    ~IndexBuffer();

    void init(std::span<const GLuint> indices);

    void Bind() const;

    void Unbind() const;
};
