#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>

#include "IndexBuffer.h"
#include "OpenGLError.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Window.h"

// Test headers
#include "tests/CameraTest.h"
#include "tests/ClearColor.h"
#include "tests/Test.h"
#include "tests/TextureTest.h"
#include "tests/Transformations.h"
#include "tests/Triangle.h"
#include "tests/LightingColors.h"
#include "tests/ZeldaLogo.h"
#include "tests/LightingApp.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Window globalWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", true);


int main(int argc, char** argv) {
  globalWindow.SetFramebufferEvent(framebuffer_size_callback);
  Renderer renderer;
  {
    std::cout << GLCall(glGetString(GL_VERSION)) << std::endl;
    GLCallV(glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(globalWindow.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    Test::Test* currentApp = nullptr;
    Test::Menu* menu = new Test::Menu(currentApp);

    menu->AddTest<Test::ClearColor>("Clear Color");
    menu->AddTest<Test::Triangle>("Triangle");
    menu->AddTest<Test::TextureTest>("Texture");
    menu->AddTest<Test::ZeldaLogo>("Zelda Logo");
    menu->AddTest<Test::Transformations>("Transformations");
    menu->AddTest<Test::CameraTest>("Camera");
    menu->AddTest<Test::LightingColors>("Lighting Colors");
    menu->AddTest<Test::LightingApp>("Lighting");

    if (argc > 1) {
      bool found = false;
      for (Test::Apps& app : menu->GetAppList()) {
        if (app.name == argv[1]) {
          currentApp = app.app();
          found = true;
          break;
        }
      }
      if (!found) {
        std::cerr << "Couldn't find " << argv[1] << " in the avaidable apps" << std::endl;
        currentApp = menu;
      }
    }
    else {
      currentApp = menu;
    }

    float deltaTime = 0.0f;

    while (!globalWindow.ShouldClose()) {
      processInput(globalWindow.GetWindow());

      renderer.SetClearColor(0.3f, 0.7f, 0.6f);
      renderer.Clear();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      if (currentApp != nullptr) {
        currentApp->OnUpdate(deltaTime);
        currentApp->OnRender();
        ImGui::Begin("Test");
        if (currentApp != menu) {
          if (ImGui::Button("<-")) {
            delete currentApp;
            currentApp = menu;
          }
          // ImGui::SameLine();
          // ImGui::SliderFloat("Delta Time", &deltaTime, 0.0f, 0.5f);
        }

        currentApp->OnImGuiRender();
        ImGui::End();
      }

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      globalWindow.OnUpdate();
    }

    delete currentApp;
    if (currentApp != menu) {
      delete menu;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  GLCallV(glViewport(0, 0, width, height));
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}