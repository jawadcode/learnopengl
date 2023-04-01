#include "index_buffer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <span>

IndexBuffer::IndexBuffer() { glGenBuffers(1, &m_index_buffer_id); }

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_index_buffer_id); }

void IndexBuffer::init(std::span<const GLuint> indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id);
}

void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }