#ifndef GOING_3D_H
#define GOING_3D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "tests/Test.h"

namespace Test {
class Going3D : public Test {
private:
  const float m_Vertices[180] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
      0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
      -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f  //
  };
  const glm::vec3 m_CubePositions[10] = {
      glm::vec3(0.0f, 0.0f, 0.0f),     //
      glm::vec3(2.0f, 5.0f, -15.0f),   //
      glm::vec3(-1.5f, -2.2f, -2.5f),  //
      glm::vec3(-3.8f, -2.0f, -12.3f), //
      glm::vec3(2.4f, -0.4f, -3.5f),   //
      glm::vec3(-1.7f, 3.0f, -7.5f),   //
      glm::vec3(1.3f, -2.0f, -2.5f),   //
      glm::vec3(1.5f, 2.0f, -2.5f),    //
      glm::vec3(1.5f, 0.2f, -1.5f),    //
      glm::vec3(-1.3f, 1.0f, -1.5f)    //
  };

  glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
  glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
  glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<VertexBuffer> m_VBO;
  std::unique_ptr<Shader> m_Shader;
  std::unique_ptr<Texture> m_CrateTexture;
  std::unique_ptr<Texture> m_AwesomefaceTexture;

  VertexBufferLayout m_Layout;
  Renderer m_Renderer;

  const std::string m_CrateFilePath = "res/textures/crate.png";
  const std::string m_AwesomefaceFilePath = "res/textures/awesomeface.png";
  const std::string m_VertexShaderFilePath = "res/shaders/3DVertex.glsl";
  const std::string m_FragmentShaderFilePath = "res/shaders/3DFragment.glsl";

public:
  Going3D();
  ~Going3D();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace Test

#endif // GOING_3D_H