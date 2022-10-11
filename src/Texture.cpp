#include "Texture.h"

#include "OpenGLError.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filePath, unsigned int type, int totComponents)
  : m_RendererID(0),
  m_FilePath(filePath),
  m_Data(nullptr),
  m_Width(0),
  m_Height(0),
  m_Tot_Channels(0),
  m_Type(type),
  m_Tot_Components(totComponents) {
  GLCallV(glGenTextures(1, &m_RendererID));
  GLCallV(glBindTexture(GL_TEXTURE_2D, m_RendererID));

  stbi_set_flip_vertically_on_load(1);
  m_Data = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_Tot_Channels, m_Tot_Components);

  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));

  GLCallV(glTexImage2D(GL_TEXTURE_2D, 0, m_Type, m_Width, m_Height, 0, m_Type, GL_UNSIGNED_BYTE, m_Data));

  GLCallV(glGenerateMipmap(GL_TEXTURE_2D));

  GLCallV(glBindTexture(GL_TEXTURE_2D, 0));

  if (m_Data) {
    stbi_image_free(m_Data);
  }
}

Texture::~Texture() { GLCallV(glDeleteTextures(1, &m_RendererID)); }

void Texture::Bind(unsigned int slot) const {
  GLCallV(glActiveTexture(GL_TEXTURE0 + slot));
  GLCallV(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const { GLCallV(glBindTexture(GL_TEXTURE_2D, 0)); }
