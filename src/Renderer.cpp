#include "Renderer.h"

#include "OpenGLError.h"

Renderer::Renderer() {}

Renderer::~Renderer() {
  if (m_DoBlending) {
    EnableBlending(false);
  }
  if (m_DoDepth) {
    EnableDepth(false);
  }
  if (m_DoStencil) {
    EnableStencil(false);
  }
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
  va.Bind();
  ib.Bind();
  shader.Bind();
  GLCallV(glDrawElements(m_Primative, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, unsigned int count, const Shader& shader) const {
  va.Bind();
  shader.Bind();
  GLCallV(glDrawArrays(m_Primative, 0, count));
}

void Renderer::Clear() const {
  unsigned int color, depth, stencil;
  color = GL_COLOR_BUFFER_BIT;
  depth = (m_DoDepth) ? GL_DEPTH_BUFFER_BIT : 0;
  stencil = (m_DoStencil) ? GL_STENCIL_BUFFER_BIT : 0;

  GLCallV(glClear(color + depth + stencil));
}

void Renderer::SetClearColor(float r, float g, float b, float a) const { GLCallV(glClearColor(r, g, b, a)); }

void Renderer::SetPrimatives(Primative primative) {
  m_Primative = primative;
}

void Renderer::EnableBlending(bool state) {
  if (state) {
    GLCallV(glEnable(GL_BLEND));
    GLCallV(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    m_DoBlending = true;
  }
  else {
    GLCallV(glDisable(GL_BLEND));
    m_DoBlending = false;
  }
}

void Renderer::EnableDepth(bool state) {
  if (state) {
    GLCallV(glEnable(GL_DEPTH_TEST));
    m_DoDepth = true;
  }
  else {
    GLCallV(glDisable(GL_DEPTH_TEST));
    m_DoDepth = false;
  }
}

void Renderer::EnableStencil(bool state) {
  if (state) {
    GLCallV(glEnable(GL_STENCIL));
    m_DoStencil = true;
  }
  else {
    GLCallV(glDisable(GL_STENCIL));
    m_DoStencil = false;
  }
}

void Renderer::EnableWireframe(bool state) {
  if (state) {
    GLCallV(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    m_DoLines = true;
  }
  else {
    GLCallV(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    m_DoLines = false;
  }
}

