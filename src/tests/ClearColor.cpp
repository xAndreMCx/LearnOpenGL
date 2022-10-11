#include "tests/ClearColor.h"

#include <imgui/imgui.h>

namespace Test {
ClearColor::ClearColor() : m_Color{ 0.0f, 0.0f, 0.0f, 1.0f } {}
ClearColor::~ClearColor() {}
void ClearColor::OnUpdate(float deltaTime) {}
void ClearColor::OnRender() {
  m_Renderer.SetClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
  m_Renderer.Clear();
}
void ClearColor::OnImGuiRender() { ImGui::ColorEdit4("Clear Color", m_Color); }

} // namespace Test