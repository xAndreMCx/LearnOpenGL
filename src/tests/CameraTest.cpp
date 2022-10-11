#include "tests/CameraTest.h"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Window.h"

// Global Camera for this file: needed for events
static Camera::Camera g_Camera = Camera::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool g_FirstMouse = true;

// TODO: Use non magic numbers
// Center of screen coords
float g_LastY = 360.0f;
float g_LastX = 640.0f;

void cursor_callback(GLFWwindow* window, double xpos, double ypos) {
  if (g_FirstMouse) {
    g_LastX = xpos;
    g_LastY = ypos;
    g_FirstMouse = false;
  }

  float xoffset = xpos - g_LastX;
  float yoffset = g_LastY - ypos;
  g_LastX = xpos;
  g_LastY = ypos;

  g_Camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  g_Camera.ProcessMouseScroll(yoffset);
}

namespace Test {
CameraTest::CameraTest() {
  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(m_Vertices, sizeof(m_Vertices));
  m_Shader = std::make_unique<Shader>(m_VertexShaderFilePath, m_FragmentShaderFilePath);

  m_CrateTexture = std::make_unique<Texture>(m_CrateFilePath, GL_RGBA);
  m_AwesomefaceTexture = std::make_unique<Texture>(m_AwesomefaceFilePath, GL_RGBA);

  m_Layout.Push(GL_FLOAT, 3); // Positions
  m_Layout.Push(GL_FLOAT, 2); // Text coords

  m_VAO->AddBuffer(*m_VBO, m_Layout);
  m_VBO->Unbind();

  m_Renderer.EnableDepth(true);

  m_CrateTexture->Bind();
  m_Shader->Bind();
  m_Shader->SetUniform1i("u_TexCrate", 0);

  m_AwesomefaceTexture->Bind(1);
  m_Shader->Bind();
  m_Shader->SetUniform1i("u_TexFace", 1);

  globalWindow.SetScrollEvent(scroll_callback);

}

CameraTest::~CameraTest() {
  globalWindow.SetCursorPosEvent(NULL);
  globalWindow.SetScrollEvent(NULL);
  m_Renderer.EnableDepth(false);
  m_VAO->Unbind();
  m_Shader->Unbind();
  m_CrateTexture->Unbind();
  m_AwesomefaceTexture->Unbind();
}

void CameraTest::OnUpdate(float deltaTime) {
  processInput(globalWindow.GetWindow());
}

void CameraTest::OnRender() {
  m_Renderer.Clear();

  m_ProjectionMatrix = glm::perspective(glm::radians(g_Camera.GetFOV()), 1280.0f / 720.0f, 0.1f, 100.0f);
  m_ViewMatrix = g_Camera.GetViewMatrix();
  m_Shader->Bind();
  m_Shader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);
  m_Shader->SetUniformMat4f("u_ProjectionMatrix", m_ProjectionMatrix);

  for (int i = 0; i < 10; i++) {
    m_ModelMatrix = glm::mat4(1.0f);
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_CubePositions[i]);
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(20.0f) * (i + 1), glm::vec3(1.0f, 0.3f, 0.5f));
    m_Shader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);

    m_Renderer.Draw(*m_VAO, 36, *m_Shader);
  }
}

void CameraTest::OnImGuiRender() {}

void CameraTest::processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    g_FirstMouse = true;
    globalWindow.SetInput(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    globalWindow.SetCursorPosEvent(cursor_callback);
  }
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    globalWindow.SetInput(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    globalWindow.SetCursorPosEvent(NULL);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    g_Camera.ProcessKeyboard(Camera::FORWARD, globalWindow.GetDeltaTime());
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    g_Camera.ProcessKeyboard(Camera::BACKWARD, globalWindow.GetDeltaTime());
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    g_Camera.ProcessKeyboard(Camera::LEFT, globalWindow.GetDeltaTime());
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    g_Camera.ProcessKeyboard(Camera::RIGHT, globalWindow.GetDeltaTime());
  }
}

} // namespace Test
