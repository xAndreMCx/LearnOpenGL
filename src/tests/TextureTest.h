#ifndef TEXTURE_TEST_H
#define TEXTURE_TEST_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "tests/Test.h"

namespace Test {
class TextureTest : public Test {
private:
  glm::vec3 m_TranslationVector;
  const glm::mat4 m_ProjectionMatrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
  const glm::mat4 m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));

  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<VertexBuffer> m_VBO;
  std::unique_ptr<VertexBufferLayout> m_Layout;
  std::unique_ptr<IndexBuffer> m_EBO;
  std::unique_ptr<Shader> m_Shader;
  Renderer m_Renderer;
  std::unique_ptr<Texture> m_CrateTexture;
  std::unique_ptr<Texture> m_AwesomefaceTexture;

  const std::string m_CrateFilePath = "res/textures/crate.png";
  const std::string m_AwesomefaceFilePath = "res/textures/awesomeface.png";
  const std::string m_VertexShaderFilePath = "res/shaders/TextureVertex.glsl";
  const std::string m_FragmentShaderFilePath = "res/shaders/TextureFragment.glsl";

public:
  TextureTest();
  ~TextureTest();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace Test

#endif // TEXTURE_TEST_H