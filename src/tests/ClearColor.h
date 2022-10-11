#ifndef CLEAR_COLOR_H
#define CLEAR_COLOR_H



#include "Renderer.h"
#include "tests/Test.h"

namespace Test {
class ClearColor : public Test {
private:
  Renderer m_Renderer;
  float m_Color[4];

public:
  ClearColor();
  ~ClearColor();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace Test
#endif // CLEAR_COLOR_H