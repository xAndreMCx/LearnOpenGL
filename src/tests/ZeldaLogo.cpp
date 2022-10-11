#include "tests/ZeldaLogo.h"

namespace Test {

ZeldaLogo::ZeldaLogo() {
  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(m_Vertices, sizeof(m_Vertices));
  m_EBO = std::make_unique<IndexBuffer>(m_Indicies, 9);
  m_Shader = std::make_unique<Shader>(m_VertexPath, m_FragmentPath);

  m_Layout.Push(GL_FLOAT, 2);
  m_VAO->AddBuffer(*m_VBO, m_Layout);
  m_VBO->Unbind();
}

ZeldaLogo::~ZeldaLogo() {
  m_VAO->Unbind();
  m_EBO->Unbind();
  m_Shader->Unbind();
}

void ZeldaLogo::OnUpdate(float deltaTime) {}

void ZeldaLogo::OnRender() {
  m_Renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
}

void ZeldaLogo::OnImGuiRender() {}

} // namespace Test
