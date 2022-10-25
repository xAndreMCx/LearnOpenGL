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
  // m_ModelMatrix = glm::mat4(1.0f);

  m_CubeShader->Bind();
  m_CubeShader->SetUniformMat4f("u_ProjectionMatrix", m_ProjectionMatrix);
  m_CubeShader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);

  m_CubeShader->SetUniform1i("u_Material.diffuse", 0);
  m_CubeShader->SetUniform1i("u_Material.specular", 1);
  m_CubeShader->SetUniform1f("u_Material.shininess", m_MaterialShininess);

  // Directional Light
  m_CubeShader->SetUniform3f("u_DirectionalLight.direction", m_DirectionalLightDirection);

  m_CubeShader->SetUniform3f("u_DirectionalLight.ambient", m_Ambient);
  m_CubeShader->SetUniform3f("u_DirectionalLight.diffuse", m_Diffuse);
  m_CubeShader->SetUniform3f("u_DirectionalLight.specular", m_Specular);

  // Point Lights
  for (int i = 0; i < 4; i++) {
    m_CubeShader->SetUniform3f("u_PointLights[" + std::to_string(i) + "].ambient", m_Ambient);
    m_CubeShader->SetUniform3f("u_PointLights[" + std::to_string(i) + "].diffuse", m_Diffuse);
    m_CubeShader->SetUniform3f("u_PointLights[" + std::to_string(i) + "].specular", m_Specular);

    m_CubeShader->SetUniform3f("u_PointLights[" + std::to_string(i) + "].position", m_PointLightPositions[i]);

    m_CubeShader->SetUniform1f("u_PointLights[" + std::to_string(i) + "].constant", m_PointLightAttenuation[i].x);
    m_CubeShader->SetUniform1f("u_PointLights[" + std::to_string(i) + "].linear", m_PointLightAttenuation[i].y);
    m_CubeShader->SetUniform1f("u_PointLights[" + std::to_string(i) + "].quadratic", m_PointLightAttenuation[i].z);
  }

  // Spot Lights
  m_CubeShader->SetUniform3f("u_SpotLight.ambient", m_Ambient);
  m_CubeShader->SetUniform3f("u_SpotLight.diffuse", m_Diffuse);
  m_CubeShader->SetUniform3f("u_SpotLight.specular", m_Specular);

  m_CubeShader->SetUniform3f("u_SpotLight.position", m_Camera.GetPosition());
  m_CubeShader->SetUniform3f("u_SpotLight.direction", m_Camera.GetFront());

  m_CubeShader->SetUniform1f("u_SpotLight.innerCutOff", glm::cos(glm::radians(12.5f)));
  m_CubeShader->SetUniform1f("u_SpotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

  m_CubeShader->SetUniform3f("u_CameraPosition", m_Camera.GetPosition());

  for (int i = 0; i < 10; i++) {
    m_ModelMatrix = glm::mat4(1.0f);
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_CubePositions[i]);
    float angle = 20.0f * i;
    m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    m_CubeShader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);
    m_Renderer.Draw(*m_CubeVAO, 36, *m_CubeShader);

  }

  m_ModelMatrix = glm::mat4(1.0f);

  m_LightShader->Bind();
  m_LightShader->SetUniformMat4f("u_ProjectionMatrix", m_ProjectionMatrix);
  m_LightShader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);

  for (int i = 0; i < 4; i++) {
    m_ModelMatrix = glm::mat4(1.0f);
    m_ModelMatrix = glm::translate(m_ModelMatrix, m_PointLightPositions[i]);
    m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.2f));
    m_LightShader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);
    m_Renderer.Draw(*m_LightVAO, *m_LightEBO, *m_LightShader);
  }

}

void LightingApp::OnImGuiRender() {
  if (ImGui::CollapsingHeader("Light")) {
    if (ImGui::CollapsingHeader("Directional Light")) {
      ImGui::SliderFloat3("Direction", &m_DirectionalLightDirection.x, -5, 5);
      ImGui::Separator();
    }
    if (ImGui::CollapsingHeader("Point Lights")) {
      for (int i = 0; i < 4; i++) {
        if (ImGui::TreeNode((void*)(intptr_t)i, "Light %d", i+1)) {
            ImGui::SliderFloat3("Position", &m_PointLightPositions[i].x, -5.0f, 5.0f);
            ImGui::SliderFloat("Constant", &m_PointLightAttenuation[i].x, 0.0f, 5.0f);
            ImGui::SliderFloat("Linear", &m_PointLightAttenuation[i].y, 0.0f, 2.5f);
            ImGui::SliderFloat("Quadratic", &m_PointLightAttenuation[i].z, 0.0f, 2.5f);
          ImGui::TreePop();
        }
      }
      ImGui::Separator();
    }
    ImGui::Spacing();

    ImGui::SliderFloat3("Ambient", &m_Ambient.x, -5, 5);
    ImGui::SliderFloat3("Diffuse", &m_Diffuse.x, -5, 5);
    ImGui::SliderFloat3("Specular", &m_Specular.x, -5, 5);
  }
    if (ImGui::CollapsingHeader("Material")) { 
      ImGui::SliderFloat("Shininess", &m_MaterialShininess, -5, 5);
    }
}

} // namespace Test
