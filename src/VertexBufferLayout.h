#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#ifndef __gl_h_
#include <GLAD/glad.h>
#endif

#include <vector>

struct vertexBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    case GL_UNSIGNED_BYTE:
      return 1;
    }
    return 0;
  }
};

class VertexBufferLayout {
private:
  std::vector<vertexBufferElement> m_Elements;
  unsigned int m_Stride;

public:
  VertexBufferLayout() : m_Stride(0) {}

  void Push(unsigned int type, unsigned int count);

  inline const std::vector<vertexBufferElement> GetElements() const& { return m_Elements; };
  inline unsigned int GetStride() const { return m_Stride; };
};

#endif  // VERTEX_BUFFER_LAYOUT_H
