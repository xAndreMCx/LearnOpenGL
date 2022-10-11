#include "tests/TextureTest.h"

namespace Test {

TextureTest::TextureTest() : m_TranslationVector(200.0f, 200.0f, 0.0f) {
  float square[] = {
    // positions    // texture coords
    500.0f, 500.0f, 0.0f, 1.0f, 1.0f, // top right
    500.0f, 200.0f, 0.0f, 1.0f, 0.0f, // bottom right
    200.0f, 200.0f, 1.0f, 0.0f, 0.0f, // bottom left
    200.0f, 500.0f, 0.0f, 0.0f, 1.0f  // top left
  };

  unsigned int squareIndicies[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(square, sizeof(square));
  m_EBO = std::make_unique<IndexBuffer>(squareIndicies, 6);
  m_Layout = std::make_unique<VertexBufferLayout>();
  m_Shader = std::make_unique<Shader>(m_VertexShaderFilePath, m_FragmentShaderFilePath);

  m_CrateTexture = std::make_unique<Texture>(m_CrateFilePath, GL_RGBA);
  m_AwesomefaceTexture = std::make_unique<Texture>(m_AwesomefaceFilePath, GL_RGBA);

  m_Layout->Push(GL_FLOAT, 3); // Positions
  m_Layout->Push(GL_FLOAT, 2); // Textures

  m_VAO->AddBuffer(*m_VBO, *m_Layout);
  m_VBO->Unbind();

  m_CrateTexture->Bind();
  m_AwesomefaceTexture->Bind(1);

  m_Shader->SetUniform1i("u_Texture1", 0);
  m_Shader->SetUniform1i("u_Texture2", 1);

  glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_TranslationVector);
  glm::mat4 MVP = m_ProjectionMatrix * m_ViewMatrix * modelMatrix;
  m_Shader->SetUniformMat4f("u_MVP", MVP);
}

TextureTest::~TextureTest() {
  m_VAO->Unbind();
  m_EBO->Unbind();
  m_Shader->Unbind();
  m_CrateTexture->Unbind();
  m_AwesomefaceTexture->Unbind();
}

void TextureTest::OnUpdate(float deltaTime) {}

void TextureTest::OnRender() {
  m_Renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
}

void TextureTest::OnImGuiRender() {}
}; // namespace Test