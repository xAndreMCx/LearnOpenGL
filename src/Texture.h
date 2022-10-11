#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef __gl_h_
#include <GLAD/glad.h>
#endif

#include <string>

class Texture {
 private:
  unsigned int m_RendererID;
  std::string m_FilePath;
  unsigned char* m_Data;
  int m_Width, m_Height, m_Tot_Channels;
  unsigned int m_Type;
  int m_Tot_Components;

 public:
  Texture(const std::string& filePath, unsigned int type = GL_RGBA, int totComponents = 4);
  ~Texture();

  void Bind(unsigned int slot = 0) const;
  void Unbind() const;
};

#endif  // TEXTURE_H
