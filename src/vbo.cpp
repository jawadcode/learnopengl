#include "vbo.hpp"

VBO::~VBO() { glDeleteBuffers(1, &m_vbo_id); }

void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id); }

void VBO::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
