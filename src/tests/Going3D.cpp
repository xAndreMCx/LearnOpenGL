#include "tests/Going3D.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Test {
Going3D::Going3D() {
  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(m_Vertices, sizeof(m_Vertices));
  m_Shader = std::make_unique<Shader>(m_VertexShaderFilePath, m_FragmentShaderFilePath);
  m_CrateTexture = std::make_unique<Texture>(m_CrateFilePath, GL_RGB, 3);
  m_AwesomefaceTexture = std::make_unique<Texture>(m_AwesomefaceFilePath, GL_RGBA);

  m_Layout.Push(GL_FLOAT, 3); // Positions
  m_Layout.Push(GL_FLOAT, 2); // Text coords

  // Add the layout of the vertex buffer to the vertex array
  // and unbinds it because it's not needed anymore
  m_VAO->AddBuffer(*m_VBO, m_Layout);
  m_VBO->Unbind();

  m_Renderer.EnableDepth();

  // Adds textures to Textures
  m_CrateTexture->Bind();
  m_AwesomefaceTexture->Bind(1);
  m_Shader->Bind();
  m_Shader->SetUniform1i("u_TexCrate", 0);
  m_Shader->SetUniform1i("u_TexFace", 1);

  m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(0.0f, 0.0f, -3.0f)); // Move "cam" back a bit
  m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f); // Adds perspective

  m_Shader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);
  m_Shader->SetUniformMat4f("u_ProjectionMatrix", m_ProjectionMatrix);
}

Going3D::~Going3D() {
  m_Renderer.EnableDepth(false);
  m_VAO->Unbind();
  m_VBO->Unbind();
  m_Shader->Unbind();
  m_CrateTexture->Unbind();
  m_AwesomefaceTexture->Unbind();

}

void Going3D::OnUpdate(float deltaTime) {}

void Going3D::OnRender() {
  m_Renderer.Clear();

  for (int i = 0; i < 10; i++) {
    m_ModelMatrix = glm::mat4(1.0f);
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_CubePositions[i]);
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(20.0f) * (i + 1), glm::vec3(1.0f, 0.3f, 0.5f));

    m_Shader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);

    m_Renderer.Draw(*m_VAO, 36, *m_Shader);
  }
}

void Going3D::OnImGuiRender() {}

} // namespace Test
