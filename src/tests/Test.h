#ifndef TEST_H
#define TEST_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "imgui/imgui.h"

namespace Test {
class Test {
private:
public:
  Test() {}
  virtual ~Test() {}

  virtual void OnUpdate(float deltaTime) {}
  virtual void OnRender() {}
  virtual void OnImGuiRender() {}
};

struct Apps {
  std::string name;
  std::function<Test* ()> app;
};

class Menu : public Test {
private:
  std::vector<Apps> m_AppList;
  Test*& m_CurrentApp;

public:
  Menu(Test*& currentApp);

  void OnImGuiRender() override;

  template <typename T> void AddTest(const std::string& name) {
    m_AppList.push_back(Apps{ name, []() { return new T(); } });
  }

  std::vector<Apps> GetAppList() const;
};

} // namespace Test

#endif // TEST_H