#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

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
class Transformations : public Test {
private:
  const float m_Vertices[20] = {
    // positions          // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
  };
  const unsigned int m_Indicies[6] = {
      0, 1, 3, // top right triangle
      1, 2, 3  // bottom left triangle
  };

  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<VertexBuffer> m_VBO;
  std::unique_ptr<IndexBuffer> m_EBO;
  std::unique_ptr<Shader> m_Shader;
  std::unique_ptr<Texture> m_CrateTexture;
  std::unique_ptr<Texture> m_AwesomefaceTexture;

  VertexBufferLayout m_Layout;
  Renderer m_Renderer;

  const std::string m_CrateFilePath = "res/textures/crate.png";
  const std::string m_AwesomefaceFilePath = "res/textures/awesomeface.png";
  const std::string m_VertexShaderFilePath =
    "res/shaders/TransformationsVertex.glsl";
  const std::string m_FragmentShaderFilePath =
    "res/shaders/TransformationsFragment.glsl";

public:
  Transformations();
  ~Transformations();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace Test

#endif // TRANSFORMATIONS_H