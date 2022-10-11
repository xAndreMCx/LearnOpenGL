#include "LightingApp.h"
#include "Window.h"

namespace Test {
void LightingApp::processInput(GLFWwindow* window) {
  if (m_CameraMode) {
    if (temp) {
      m_FirstMouse = true;
      globalWindow.SetInput(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      globalWindow.SetCursorPosEvent(cursor_callback);
      globalWindow.SetScrollEvent(scroll_callback);
      temp = false;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      m_Camera.ProcessKeyboard(Camera::FORWARD, globalWindow.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      m_Camera.ProcessKeyboard(Camera::BACKWARD, globalWindow.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      m_Camera.ProcessKeyboard(Camera::LEFT, globalWindow.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      m_Camera.ProcessKeyboard(Camera::RIGHT, globalWindow.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
      m_Camera.ProcessKeyboard(Camera::UP, globalWindow.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
      m_Camera.ProcessKeyboard(Camera::DOWN, globalWindow.GetDeltaTime());
    }
  }
  else {
    globalWindow.SetInput(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    globalWindow.SetCursorPosEvent(NULL);
    globalWindow.SetScrollEvent(NULL);
    temp = true;
  }
}
void LightingApp::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
  if (m_FirstMouse) {
    m_LastX = xpos;
    m_LastY = ypos;
    m_FirstMouse = false;
  }

  float xoffset = xpos - m_LastX;
  float yoffset = m_LastY - ypos;
  m_LastX = xpos;
  m_LastY = ypos;
  m_Camera.ProcessMouseMovement(xoffset, yoffset);
}
void LightingApp::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  m_Camera.ProcessMouseScroll(yoffset);
}
void LightingApp::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    m_CameraMode = !m_CameraMode;
  }
}

Camera::Camera LightingApp::m_Camera(glm::vec3(1.0f, 1.0f, 5.0f));
bool LightingApp::m_FirstMouse{ true };
float LightingApp::m_LastX{ globalWindow.GetWidth() / 2.0f };
float LightingApp::m_LastY{ globalWindow.GetHeight() / 2.0f };


LightingApp::LightingApp() {
  m_CubeVAO = std::make_unique<VertexArray>();
  m_CubeVBO = std::make_unique<VertexBuffer>(m_CubeVertices, sizeof(m_CubeVertices));
  m_CubeShader = std::make_unique<Shader>(m_CubeVertexPath, m_CubeFragmentPath);
  m_CubeDiffuseTexture = std::make_unique<Texture>(m_CubeDiffuseTexturePath);
  m_CubeSpecularTexture = std::make_unique<Texture>(m_CubeSpecularTexturePath);

  m_CubeLayout.Push(GL_FLOAT, 3);
  m_CubeLayout.Push(GL_FLOAT, 3);
  m_CubeLayout.Push(GL_FLOAT, 2);

  m_CubeVAO->AddBuffer(*m_CubeVBO, m_CubeLayout);
  m_CubeVBO->Unbind();

  m_CubeDiffuseTexture->Bind();
  m_CubeSpecularTexture->Bind(1);

  m_LightVAO = std::make_unique<VertexArray>();
  m_LightEBO = std::make_unique<IndexBuffer>(m_LightIndicies, 36);
  m_LightShader = std::make_unique<Shader>(m_LightVertexPath, m_LightFragmentPath);
  m_LightVBO = std::make_unique<VertexBuffer>(m_LightVertices, sizeof(m_LightVertices));
  m_LightLayout.Push(GL_FLOAT, 3);
  m_LightVAO->AddBuffer(*m_LightVBO, m_LightLayout);
  m_LightVBO->Unbind();


  m_Renderer.EnableDepth(true);
  globalWindow.SetKeyEvent(key_callback);
}

LightingApp::~LightingApp() {
  globalWindow.SetCursorPosEvent(NULL);
  globalWindow.SetScrollEvent(NULL);
  globalWindow.SetKeyEvent(NULL);

  m_Renderer.EnableDepth(false);

  m_CubeVAO->Unbind();
  m_LightVAO->Unbind();
  m_LightEBO->Unbind();
  m_CubeShader->Unbind();
  m_LightShader->Unbind();
  m_CubeDiffuseTexture->Unbind();
  m_CubeSpecularTexture->Unbind();
}

void LightingApp::OnUpdate(float deltaTime) {
  processInput(globalWindow.GetWindow());
}

void LightingApp::OnRender() {
  m_Renderer.SetClearColor(0.1f, 0.1f, 0.1f);
  m_Renderer.Clear();

  m_ProjectionMatrix = m_Camera.GetProjectionMatrix();
  m_ViewMatrix = m_Camera.GetViewMatrix();
  m_ModelMatrix = glm::mat4(1.0f);

  m_CubeShader->Bind();
  m_CubeShader->SetUniformMat4f("u_ProjectionMatrix", m_ProjectionMatrix);
  m_CubeShader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);
  m_CubeShader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);

  m_CubeShader->SetUniform1i("u_Material.Diffuse", 0);
  m_CubeShader->SetUniform1i("u_Material.Specular", 1);
  m_CubeShader->SetUniform1f("u_Material.Shininess", m_MaterialShininess);

  m_CubeShader->SetUniform3f("u_Light.Ambient", m_LightAmbient.x, m_LightAmbient.y, m_LightAmbient.z);
  m_CubeShader->SetUniform3f("u_Light.Diffuse", m_LightDiffuse.x, m_LightDiffuse.y, m_LightDiffuse.z);
  m_CubeShader->SetUniform3f("u_Light.Specular", m_LightSpecular.x, m_LightSpecular.y, m_LightSpecular.z);
  m_CubeShader->SetUniform3f("u_Light.Position", m_LightPosition.x, m_LightPosition.y, m_LightPosition.z);
  m_CubeShader->SetUniform3f("u_Light.Color", m_LightColor.r, m_LightColor.g, m_LightColor.b);


  m_CubeShader->SetUniform3f("u_CameraPosition", m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z);


  m_Renderer.Draw(*m_CubeVAO, 36, *m_CubeShader);

  m_ModelMatrix = glm::mat4(1.0f);

  m_LightShader->Bind();
  m_LightShader->SetUniformMat4f("u_ProjectionMatrix", m_ProjectionMatrix);
  m_LightShader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);
  m_ModelMatrix = glm::translate(m_ModelMatrix, m_LightPosition);
  m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.2f));
  m_LightShader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);
  m_LightShader->SetUniform3f("u_LightColor", m_LightColor.r, m_LightColor.g, m_LightColor.b);

  m_Renderer.Draw(*m_LightVAO, *m_LightEBO, *m_LightShader);
}

void LightingApp::OnImGuiRender() {

}

} // namespace Test
