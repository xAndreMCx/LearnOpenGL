#include "IndexBuffer.h"

#include <GLAD/glad.h>

#include "OpenGLError.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
    : m_Count(count) {
  GLCallV(glGenBuffers(1, &m_ID));
  GLCallV(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
  GLCallV(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
                       data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() { GLCallV(glDeleteBuffers(1, &m_ID)); }

void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }
void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
