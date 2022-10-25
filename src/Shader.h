#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader {
private:
  std::string m_vertexPath;
  std::string m_fragmentPath;
  unsigned int m_RendererID;
  std::unordered_map<std::string, int> m_UniformLocationCache;

  int GetUniformLocation(const std::string& name);
  unsigned int CompileShader(unsigned int type, std::string& source);
  unsigned int CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

public:
  Shader(const std::string& vertexPath, const std::string& fragmentPath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  void SetUniform1f(const std::string& name, float value);
  void SetUniform3f(const std::string& name, float v0, float v1, float v2);
  void SetUniform3f(const std::string& name, glm::vec3 value);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void SetUniform1i(const std::string& name, int value);

  void SetUniformMat4f(const std::string& name, const glm::mat4 value);
};

#endif  // SHADER_H
