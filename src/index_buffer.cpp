#include "index_buffer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <span>

IndexBuffer::IndexBuffer(const std::span<GLuint> indices)
    : m_count(indices.size()) {
    glGenBuffers(1, &m_index_buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(GLuint),
                 indices.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_index_buffer_id); }

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id);
}

void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }