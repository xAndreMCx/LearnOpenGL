#ifndef LIGHTING_COLORS_H
#define LIGHTING_COLORS_H

#include "tests/Test.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace Test {
class LightingColors : public Test
{
private:
  const float m_CubeVertices[216] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
  unsigned int m_LightIndicies[36] = {
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

  std::unique_ptr<VertexArray> m_CubeVAO;
  std::unique_ptr<VertexBuffer> m_CubeVBO;
  std::unique_ptr<Shader> m_CubeShader;
  VertexBufferLayout m_CubeLayout;

  std::unique_ptr<VertexArray> m_LightVAO;
  std::unique_ptr<IndexBuffer> m_LightEBO;
  std::unique_ptr<VertexBuffer> m_LightVBO;
  std::unique_ptr<Shader> m_LightShader;
  VertexBufferLayout m_LightLayout;

  Renderer m_Renderer;

  glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
  glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
  glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

  glm::vec3 m_LightColor = glm::vec3(1.0f, 1.0f, 1.0f);

  glm::vec3 m_LightPosition = glm::vec3(1.2f, 1.0f, 2.0f);

  glm::vec3 m_MaterialAmbient = glm::vec3(1.0f, 0.5f, 0.31f);
  glm::vec3 m_MaterialDiffuse = glm::vec3(1.0f, 0.5f, 0.31f);
  glm::vec3 m_MaterialSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
  float m_MaterialShininess = 32.0f;

  glm::vec3 m_LightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
  glm::vec3 m_LightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
  glm::vec3 m_LightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

  static Camera::Camera m_Camera;

  static float m_LastY;
  static float m_LastX;
  static bool m_FirstMouse;

  inline static bool m_CameraMode{ false };

  const std::string m_CubeVertexPath = "res/shaders/ColorsCubeVertex.glsl";
  const std::string m_CubeFragmentPath = "res/shaders/ColorsCubeFragment.glsl";
  const std::string m_LightVertexPath = "res/shaders/ColorsLightVertex.glsl";
  const std::string m_LightFragmentPath = "res/shaders/ColorsLightFragment.glsl";

  void processInput(GLFWwindow* window);
  static void cursor_callback(GLFWwindow* window, double xpos, double ypos);
  static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
  LightingColors();
  ~LightingColors();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace Test

#endif // LIGHTING_COLORS_H