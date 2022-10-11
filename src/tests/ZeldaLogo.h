#ifndef ZELDA_LOGO_H
#define ZELDA_LOGO_H

#include <memory>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "tests/Test.h"

namespace Test {
class ZeldaLogo : public Test {
private:
  const float m_Vertices[12] = {
    0.00f,  0.50f,
    0.50f, -0.50f,
   -0.50f, -0.50f,
   -0.25f,  0.00f,
    0.25f,  0.00f,
    0.00f, -0.50f
  };
  const unsigned int m_Indicies[9] = { 2, 5, 3, 5, 1, 4, 3, 4, 0 };
  const std::string m_VertexPath = "res/shaders/BasicVertex.glsl";
  const std::string m_FragmentPath = "res/shaders/BasicFragment.glsl";

  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<VertexBuffer> m_VBO;
  std::unique_ptr<IndexBuffer> m_EBO;
  std::unique_ptr<Shader> m_Shader;

  VertexBufferLayout m_Layout;
  Renderer m_Renderer;

public:
  ZeldaLogo();
  ~ZeldaLogo();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace Test
#endif // ZELDA_LOGO_H