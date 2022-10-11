#include "VertexArray.h"

#include "OpenGLError.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
  GLCallV(glGenVertexArrays(1, &m_RendererID));
  GLCallV(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray() { GLCallV(glDeleteBuffers(1, &m_RendererID)); }

void VertexArray::Bind() const { GLCallV(glBindVertexArray(m_RendererID)); }

void VertexArray::Unbind() const { GLCallV(glBindVertexArray(0)); }

void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout) {
  vb.Bind();
  const auto& elements = layout.GetElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    GLCallV(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                                  (void*)(intptr_t)offset));
    GLCallV(glEnableVertexAttribArray(i));
    offset += element.count * vertexBufferElement::GetSizeOfType(element.type);
  }
}