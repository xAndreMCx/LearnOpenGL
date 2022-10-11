#include "Window.h"

#include <iostream>
#include <imgui/imgui_impl_glfw.h>


void Window::Init() {
  // Initializes GLFW
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  // Creates Window
  m_Window = glfwCreateWindow(m_Width, m_Heigth, m_Title.c_str(), NULL, NULL);

  if (!m_Window) {
    throw std::runtime_error("Failed to create GLFW window");
  }

  SetCurrentContex();

  glfwWindowHint(GL_MAJOR_VERSION, 3);
  glfwWindowHint(GL_MINOR_VERSION, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Creates GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize OpenGL context, GLAD");
  }
}

Window::Window(int width, int height, std::string title, bool vsync)
  : m_Width(width), m_Heigth(height), m_Title(title), m_VSync(vsync), m_DeltaTime(0.0f), m_LastFrameTime(0.0f) {
  try {
    Init();
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  m_IsInitialized = true;
}

Window::~Window() {
  if (m_IsInitialized) {
    glfwTerminate();
  }
  if (m_Window != nullptr) {
    glfwDestroyWindow(m_Window);
  }
}

void Window::SetCurrentContex() { glfwMakeContextCurrent(m_Window); }

void Window::SetTitle(std::string title) { glfwSetWindowTitle(m_Window, title.c_str()); }

void Window::SetInput(int mode, int value) { glfwSetInputMode(m_Window, mode, value); }

void Window::OnUpdate() {
  m_DeltaTime = glfwGetTime() - m_LastFrameTime;
  m_LastFrameTime = glfwGetTime();

  glfwSwapBuffers(m_Window);
  glfwPollEvents();
}

void Window::SetFramebufferEvent(GLFWframebuffersizefun func) {
  glfwSetFramebufferSizeCallback(m_Window, func);
}

void Window::SetKeyEvent(GLFWkeyfun func) {
  if (func == NULL) {
    glfwSetKeyCallback(m_Window, ImGui_ImplGlfw_KeyCallback);
  }
  glfwSetKeyCallback(m_Window, func);
}

void Window::SetCursorPosEvent(GLFWcursorposfun func) {
  if (func == NULL) {
    glfwSetCursorPosCallback(m_Window, ImGui_ImplGlfw_CursorPosCallback);
  }
  else {
    glfwSetCursorPosCallback(m_Window, func);
  }
}

void Window::SetScrollEvent(GLFWscrollfun func) {
  if (func == NULL) {
    glfwSetScrollCallback(m_Window, ImGui_ImplGlfw_ScrollCallback);
  }
  glfwSetScrollCallback(m_Window, func);
}

void Window::Close() { glfwSetWindowShouldClose(m_Window, true); }

float Window::GetDeltaTime() const {
  return m_DeltaTime;
}
bool Window::ShouldClose() { return glfwWindowShouldClose(m_Window); }

GLFWwindow* Window::GetWindow() const { return m_Window; }

float Window::GetWidth() const {
  return m_Width;
}

float Window::GetHeight() const {
  return m_Heigth;
}


