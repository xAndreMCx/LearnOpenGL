#ifndef LIGHTING_APP_H
#define LIGHTING_APP_H

#include "tests/Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


namespace Test {
class LightingApp : public Test
{
private:
  const float m_CubeVertices[288] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
  };
  const float m_LightVertices[24] = {
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f
  };
  const unsigned int m_LightIndicies[36] = {
    0, 1, 5,
    5, 0, 4,
    4, 5, 6,
    6, 4, 7,
    7, 6, 2,
    2, 7, 3,
    3, 2, 1,
    1, 0, 3,
    0, 3, 7,
    7, 0, 4,
    1, 5, 2,
    2, 5, 6
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
  // Cube
  std::unique_ptr<VertexArray> m_CubeVAO;
  std::unique_ptr<VertexBuffer> m_CubeVBO;
  std::unique_ptr<Shader> m_CubeShader;
  std::unique_ptr<Texture> m_CubeDiffuseTexture;
  std::unique_ptr<Texture> m_CubeSpecularTexture;
  VertexBufferLayout m_CubeLayout;
  const std::string m_CubeVertexPath = "res/shaders/lighting_app/CubeVertex.glsl";
  const std::string m_CubeFragmentPath = "res/shaders/lighting_app/CubeFragment.glsl";
  const std::string m_CubeDiffuseTexturePath = "res/textures/steel_container.png";
  const std::string m_CubeSpecularTexturePath = "res/textures/steel_container_specular.png";

  // Light
  std::unique_ptr<VertexArray> m_LightVAO;
  std::unique_ptr<IndexBuffer> m_LightEBO;
  std::unique_ptr<VertexBuffer> m_LightVBO;
  std::unique_ptr<Shader> m_LightShader;
  VertexBufferLayout m_LightLayout;
  const std::string m_LightVertexPath = "res/shaders/lighting_app/LightVertex.glsl";
  const std::string m_LightFragmentPath = "res/shaders/lighting_app/LightFragment.glsl";

  Renderer m_Renderer;

  // MVP
  glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
  glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
  glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

  bool temp{ true };
  static Camera::Camera m_Camera;
  inline static bool m_CameraMode;
  static bool m_FirstMouse;
  static float m_LastX;
  static float m_LastY;

  glm::vec3 m_MaterialSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
  float m_MaterialShininess = 32.0f;

  glm::vec3 m_LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 m_LightPosition = glm::vec3(1.2f, 1.0f, 2.0f);
  glm::vec3 m_LightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
  glm::vec3 m_LightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
  glm::vec3 m_LightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
  glm::vec3 m_LightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

  void processInput(GLFWwindow* window);
  static void cursor_callback(GLFWwindow* window, double xpos, double ypos);
  static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
  LightingApp();
  ~LightingApp();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace Test


#endif // LIGHTING_APP_H