#include "vbo.hpp"

VBO::~VBO() { glDeleteBuffers(1, &m_vbo_id); }

void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id); }

void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
