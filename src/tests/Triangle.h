#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <memory>

#include "Renderer.h"
#include "tests/Test.h"

namespace Test {
class Triangle : public Test {
private:
  const float m_Positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };
  const std::string m_VertexShaderPath = "res/shaders/BasicVertex.glsl";
  const std::string m_FragmentShaderPath = "res/shaders/BasicFragment.glsl";

  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<VertexBuffer> m_VBO;
  std::unique_ptr<Shader> m_Shader;

  VertexBufferLayout m_Layout;
  Renderer m_Renderer;

  bool m_DrawPoints{ false };

public:
  Triangle();
  ~Triangle();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};

} // namespace Test
#endif // TRIANGLE_H