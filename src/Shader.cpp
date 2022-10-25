#include "Shader.h"

#include <GLAD/glad.h>

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <sstream>

#include "OpenGLError.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
  : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath), m_RendererID(0) {
  m_RendererID = CreateShader(vertexPath, fragmentPath);
  GLCallV(glUseProgram(m_RendererID));
}

Shader::~Shader() { GLCallV(glDeleteProgram(m_RendererID)); }

unsigned int Shader::CompileShader(unsigned int type, std::string& source) {
  unsigned int id = GLCall(glCreateShader(type));
  const char* src = source.c_str();
  GLCallV(glShaderSource(id, 1, &src, nullptr));
  GLCallV(glCompileShader(id));

  int result;
  GLCallV(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (!result) {
    int length;
    GLCallV(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    std::unique_ptr<char[]> infoLog = std::make_unique<char[]>(length);
    GLCallV(glGetShaderInfoLog(id, length, NULL, infoLog.get()));
    std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader failed to compile:\n"
      << infoLog.get() << std::endl;
    GLCallV(glDeleteShader(id));
    return 0;
  }
  return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  std::ifstream vertexShaderFile(vertexShaderPath);
  std::ifstream fragmentShaderFile(fragmentShaderPath);

  std::string line;
  std::stringstream vertexShaderSS;
  std::stringstream fragmentShaderSS;

  while (std::getline(vertexShaderFile, line)) {
    vertexShaderSS << line << '\n';
  }

  while (std::getline(fragmentShaderFile, line)) {
    fragmentShaderSS << line << '\n';
  }

  vertexShaderFile.close();
  fragmentShaderFile.close();

  std::string vertexCode = vertexShaderSS.str();
  std::string fragmentCode = fragmentShaderSS.str();

  unsigned int program = GLCall(glCreateProgram());
  unsigned int vertexShader = GLCall(CompileShader(GL_VERTEX_SHADER, vertexCode));
  unsigned int fragmentShader = GLCall(CompileShader(GL_FRAGMENT_SHADER, fragmentCode));

  GLCallV(glAttachShader(program, vertexShader));
  GLCallV(glAttachShader(program, fragmentShader));
  GLCallV(glLinkProgram(program));
  GLCallV(glValidateProgram(program));

  int result;
  GLCallV(glGetProgramiv(program, GL_VALIDATE_STATUS, &result));
  if (!result) {
    int length;
    GLCallV(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
    std::unique_ptr<char[]> infoLog = std::make_unique<char[]>(length);
    GLCallV(glGetProgramInfoLog(program, length, NULL, infoLog.get()));
    std::cout << "Program failed validation:\n" << infoLog.get() << std::endl;
  }

  GLCallV(glDeleteShader(vertexShader));
  GLCallV(glDeleteShader(fragmentShader));

  return program;
}

void Shader::Bind() const { GLCallV(glUseProgram(m_RendererID)); }

void Shader::Unbind() const { GLCallV(glUseProgram(0)); }

int Shader::GetUniformLocation(const std::string& name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    return m_UniformLocationCache[name];
  }
  int location = GLCall(glGetUniformLocation(m_RendererID, name.c_str()));
  if (location == -1) {
    std::cout << "Warning: Uniform " << name << " does not exist" << std::endl;
  }
  m_UniformLocationCache[name] = location;
  return location;
}

void Shader::SetUniform1i(const std::string& name, int value) { GLCallV(glUniform1i(GetUniformLocation(name), value)); }

void Shader::SetUniform1f(const std::string& name, float value) {
  GLCallV(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
  GLCallV(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 value) {
  GLCallV(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  GLCallV(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4 value) {
  GLCallV(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
}