#include "LightingColors.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui_impl_glfw.h>


#include "Camera.h"
#include "Window.h"

bool enableLines = false;
bool temp;

namespace Test {
void LightingColors::processInput(GLFWwindow* window) {
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
  }
  else {
    globalWindow.SetInput(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    globalWindow.SetCursorPosEvent(NULL);
    globalWindow.SetScrollEvent(NULL);
    temp = true;
  }

}

bool LightingColors::m_FirstMouse{ false };
float LightingColors::m_LastX{ 640.0f };
float LightingColors::m_LastY{ 360.0f };
Camera::Camera LightingColors::m_Camera(glm::vec3(1.0f, 1.0f, 5.0f));


LightingColors::LightingColors() {
  std::cout << "Creating app: Lighting Cololrs" << std::endl;
  m_CubeVAO = std::make_unique<VertexArray>();
  std::cout << "Creating VAO" << std::endl;

  m_CubeShader = std::make_unique<Shader>(m_CubeVertexPath, m_CubeFragmentPath);
  std::cout << "Creating Shader" << std::endl;

  m_CubeVBO = std::make_unique<VertexBuffer>(m_CubeVertices, sizeof(m_CubeVertices));
  std::cout << "Creating VBO" << std::endl;

  m_CubeLayout.Push(GL_FLOAT, 3);
  std::cout << "Creating layout1" << std::endl;

  m_CubeLayout.Push(GL_FLOAT, 3);
  std::cout << "Creating layout2" << std::endl;

  m_CubeVAO->AddBuffer(*m_CubeVBO, m_CubeLayout);
  m_CubeVBO->Unbind();
  std::cout << "Cube Setup" << std::endl;


  m_LightVAO = std::make_unique<VertexArray>();
  m_LightEBO = std::make_unique<IndexBuffer>(m_LightIndicies, 36);
  m_LightShader = std::make_unique<Shader>(m_LightVertexPath, m_LightFragmentPath);
  m_LightVBO = std::make_unique<VertexBuffer>(m_LightVertices, sizeof(m_LightVertices));
  m_LightLayout.Push(GL_FLOAT, 3);
  m_LightVAO->AddBuffer(*m_LightVBO, m_LightLayout);
  m_LightVBO->Unbind();
  std::cout << "Light Setup" << std::endl;


  m_Renderer.EnableDepth(true);
  m_Renderer.EnableWireframe(false);

  enableLines = false;
  temp = true;

  m_Camera = Camera::Camera(glm::vec3(1.0f, 1.0f, 5.0f));

  globalWindow.SetScrollEvent(scroll_callback);
  globalWindow.SetKeyEvent(key_callback);
  std::cout << "Done" << std::endl;
}

LightingColors::~LightingColors() {
  globalWindow.SetCursorPosEvent(NULL);
  globalWindow.SetScrollEvent(NULL);
  globalWindow.SetKeyEvent(NULL);

  m_Renderer.EnableDepth(false);
  m_Renderer.EnableWireframe(false);

  m_CubeVAO->Unbind();
  m_LightVAO->Unbind();
  m_LightEBO->Unbind();
  m_CubeShader->Unbind();
  m_LightShader->Unbind();

}

void LightingColors::OnUpdate(float deltaTime) {
  m_Renderer.EnableWireframe(enableLines);
  processInput(globalWindow.GetWindow());
}

void LightingColors::OnRender() {
  m_Renderer.SetClearColor(0.1f, 0.1f, 0.1f);
  m_Renderer.Clear();

  m_ProjectionMatrix = m_Camera.GetProjectionMatrix();
  m_ViewMatrix = m_Camera.GetViewMatrix();
  m_ModelMatrix = glm::mat4(1.0f);

  m_CubeShader->Bind();
  m_CubeShader->SetUniformMat4f("u_ProjectionMatrix", m_ProjectionMatrix);
  m_CubeShader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);
  m_CubeShader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);

  m_CubeShader->SetUniform3f("u_Material.Ambient", m_MaterialAmbient.x, m_MaterialAmbient.y, m_MaterialAmbient.z);
  m_CubeShader->SetUniform3f("u_Material.Diffuse", m_MaterialDiffuse.x, m_MaterialDiffuse.y, m_MaterialDiffuse.z);
  m_CubeShader->SetUniform3f("u_Material.Specular", m_MaterialSpecular.x, m_MaterialSpecular.y, m_MaterialSpecular.z);
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

void LightingColors::OnImGuiRender() {
  ImGui::ColorEdit3("Light Color", &m_LightColor.r);
  ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float);

  ImGui::ColorEdit3("Material Ambient", &m_MaterialAmbient.r);
  ImGui::SliderFloat3("Material Diffuse", &m_MaterialDiffuse.r, 0.1f, 1.0f);
  ImGui::SliderFloat3("Material Specular", &m_MaterialSpecular.r, 0.1f, 1.0f);

  // ImGui::SliderFloat3("Light Ambient", &m_LightAmbient.r, 0.1f, 1.0f);
  // ImGui::SliderFloat3("Light Diffuse", &m_LightDiffuse.r, 0.1f, 1.0f);
  // ImGui::SliderFloat3("Light Specular", &m_LightSpecular.r, 0.1f, 1.0f);

  ImGui::Text("Light Position");
  ImGui::BeginGroup();
  ImGui::SliderFloat("x", &m_LightPosition.x, -10.0f, 10.0f);
  ImGui::SliderFloat("y", &m_LightPosition.y, -10.0f, 10.0f);
  ImGui::SliderFloat("z", &m_LightPosition.z, -10.0f, 10.0f);
  ImGui::EndGroup();
}


void LightingColors::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
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

void LightingColors::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  m_Camera.ProcessMouseScroll(yoffset);
}
void LightingColors::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_L && action == GLFW_PRESS) {
    enableLines = !enableLines;
  }
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    m_CameraMode = !m_CameraMode;
  }
}
} // namespace Test


