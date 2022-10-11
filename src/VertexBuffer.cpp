#include "vertexBuffer.h"

#include <GLAD/glad.h>

#include "OpenGLError.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
  GLCallV(glGenBuffers(1, &m_RendererID));
  GLCallV(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  GLCallV(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() { GLCallV(glDeleteBuffers(1, &m_RendererID)); }

void VertexBuffer::Bind() const { GLCallV(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); }

void VertexBuffer::Unbind() const { GLCallV(glBindBuffer(GL_ARRAY_BUFFER, 0)); }