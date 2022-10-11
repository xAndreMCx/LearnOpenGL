#ifndef OPENGL_ERROR_H
#define OPENGL_ERROR_H

#ifndef __gl_h_
#include <GLAD/glad.h>
#endif

#include <cassert>
#include <iostream>

#define GLCallV(x) \
  GLClearErrors(); \
  x;               \
  assert(GLLogCall(#x, __FILE__, __LINE__))

#define GLCall(x)                              \
  [&]() {                                      \
    GLClearErrors();                           \
    auto retVal = x;                           \
    assert(GLLogCall(#x, __FILE__, __LINE__)); \
    return retVal;                             \
  }()

static void GLClearErrors() {
  while (glGetError() != GL_NO_ERROR) {
  }
}

static bool GLLogCall(const char* function, const char* file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}

#endif  // OPENGL_ERROR_H
