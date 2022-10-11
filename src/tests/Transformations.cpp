#include "tests/Transformations.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Test {

Transformations::Transformations() {
  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(m_Vertices, sizeof(m_Vertices));
  m_EBO = std::make_unique<IndexBuffer>(m_Indicies, 6);
  m_Shader = std::make_unique<Shader>(m_VertexShaderFilePath,
                                      m_FragmentShaderFilePath);

  m_CrateTexture = std::make_unique<Texture>(m_CrateFilePath, GL_RGBA);
  m_AwesomefaceTexture =
      std::make_unique<Texture>(m_AwesomefaceFilePath, GL_RGBA);

  m_Layout.Push(GL_FLOAT, 3); // Positions
  m_Layout.Push(GL_FLOAT, 2); // Text coords

  m_VAO->AddBuffer(*m_VBO, m_Layout);

  // GLCallV(glEnable(GL_BLEND));
  // GLCallV(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  m_CrateTexture->Bind();
  m_Shader->Bind();
  m_Shader->SetUniform1i("u_TexCrate", 0);

  m_AwesomefaceTexture->Bind(1);
  m_Shader->Bind();
  m_Shader->SetUniform1i("u_TexFace", 1);
}

Transformations::~Transformations() {}

void Transformations::OnUpdate(float deltaTime) {}

void Transformations::OnRender() {
  m_CrateTexture->Bind();
  m_AwesomefaceTexture->Bind(1);

  glm::mat4 transformMatrix = glm::mat4(1.0f);
  // Rotate by 90 degrees
  // transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f),
  // glm::vec3(0.0f, 0.0f, 1.0f)); transformMatrix = glm::scale(transformMatrix,
  // glm::vec3(0.5f, 0.5f, 0.5f));

  // Rotate continuously
  transformMatrix =
      glm::translate(transformMatrix, glm::vec3(0.25f, -0.25f, 0.0f));
  transformMatrix = glm::rotate(transformMatrix, (float)glfwGetTime(),
                                glm::vec3(0.0f, 0.0f, 1.0f));

  // Translate origin and rotate around new origin
  // transformMatrix = glm::rotate(transformMatrix, (float)glfwGetTime(),
  // glm::vec3(0.0f, 0.0f, 1.0f)); transformMatrix =
  // glm::translate(transformMatrix, glm::vec3(0.25f, -0.25f, 0.0f));

  m_Shader->Bind();
  m_Shader->SetUniformMat4f("u_Transform", transformMatrix);

  m_CrateTexture->Bind();
  m_AwesomefaceTexture->Bind(1);

  m_Renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
}

void Transformations::OnImGuiRender() {}

} // namespace Test
