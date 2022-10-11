#include "tests/Test.h"

namespace Test {
Menu::Menu(Test*& currentApp) : m_CurrentApp(currentApp) {}

void Menu::OnImGuiRender() {
  for (Apps& app : m_AppList) {
    if (ImGui::Button(app.name.c_str())) {
      m_CurrentApp = app.app();
      break;
    }
  }
}

std::vector<Apps> Menu::GetAppList() const { return m_AppList; }

} // namespace Test