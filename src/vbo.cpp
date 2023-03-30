#include "vbo.hpp"

VBO::VBO() { glGenBuffers(1, &m_vbo_id); }

VBO::~VBO() { glDeleteBuffers(1, &m_vbo_id); }

void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id); }

void VBO::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
