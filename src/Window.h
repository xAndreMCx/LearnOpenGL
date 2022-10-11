#ifndef WINDOW_H
#define WINDOW_H

#ifndef __gl_h_
#include <GLAD/glad.h>
#endif

#include <GLFW/glfw3.h>

#include <string>

class Window {
private:
  inline static GLFWwindow* m_Window;
  int m_Width, m_Heigth;
  std::string m_Title;
  bool m_VSync, m_IsInitialized;
  float m_DeltaTime, m_LastFrameTime;

  void Init();

public:
  Window(int width, int height, std::string title, bool vsync);
  ~Window();

  void SetCurrentContex();
  void SetTitle(std::string title);
  static void SetInput(int mode, int value);

  void OnUpdate();
  void SetFramebufferEvent(GLFWframebuffersizefun func);
  void SetKeyEvent(GLFWkeyfun func);
  void SetCursorPosEvent(GLFWcursorposfun func);
  void SetScrollEvent(GLFWscrollfun func);

  void Close();
  bool ShouldClose();

  float GetDeltaTime() const;
  GLFWwindow* GetWindow() const;
  float GetWidth() const;
  float GetHeight() const;
};

extern Window globalWindow;

#endif // WINDOW_H
