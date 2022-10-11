#ifndef RENDERER_H
#define RENDERER_H

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

typedef unsigned int Primative;
namespace DrawPrivatives {
static const Primative Triangles = 4;
static const Primative Points = 0;
static const Primative Lines = 1;
}

class Renderer {
private:
  bool m_DoBlending{ false };
  bool m_DoColor{ true };
  bool m_DoDepth{ false };
  bool m_DoStencil{ false };
  bool m_DoLines{ false };
  Primative m_Primative{ DrawPrivatives::Triangles };

public:
  Renderer();
  ~Renderer();

  void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
  void Draw(const VertexArray& va, unsigned int count, const Shader& shader) const;
  void Clear() const;
  void SetClearColor(float r, float g, float b, float a = 1.0f) const;
  void SetPrimatives(Primative primative);
  void EnableBlending(bool state = true);
  void EnableDepth(bool state = true);
  void EnableStencil(bool state = true);
  void EnableWireframe(bool state = true);

  // make a struct/namespace for all primitive type
  // set primative with SetPrimative defualt triangle

};

#endif // RENDERER_H
