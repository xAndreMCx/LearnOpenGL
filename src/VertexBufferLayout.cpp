#include "VertexBufferLayout.h"

void VertexBufferLayout::Push(unsigned int type, unsigned int count) {
  m_Elements.push_back({type, count, 0});  // 0 = GL_FALSE
  m_Stride += count * vertexBufferElement::GetSizeOfType(type);
}