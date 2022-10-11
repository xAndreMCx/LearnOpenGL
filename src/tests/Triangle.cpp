#include "tests/Triangle.h"

namespace Test {
Triangle::Triangle() {
  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(m_Positions, sizeof(m_Positions));
  m_Shader = std::make_unique<Shader>(m_VertexShaderPath, m_FragmentShaderPath);

  m_Layout.Push(GL_FLOAT, 2);
  m_VAO->AddBuffer(*m_VBO, m_Layout);
  m_VBO->Unbind();
}

Triangle::~Triangle() {
  m_VAO->Unbind();
  m_Shader->Unbind();
}

void Triangle::OnUpdate(float deltaTime) {}

void Triangle::OnRender() {
  if (m_DrawPoints) {
    m_Renderer.SetPrimatives(DrawPrivatives::Points);
    glPointSize(10.0f);
  }
  else {
    m_Renderer.SetPrimatives(DrawPrivatives::Triangles);
  }
  m_Renderer.Draw(*m_VAO, 3, *m_Shader);
}

void Triangle::OnImGuiRender() {
  ImGui::Checkbox("Points", &m_DrawPoints);
}
} // namespace Test
