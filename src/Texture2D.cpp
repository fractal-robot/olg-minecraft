#include <iostream>
#define STB_IMAGE_IMPLEMENTATION

#include "../libs/glad/include/glad/glad.h"
#include "Texture2D.h"
#include <string>

#include "../libs/stb/stb_image.h"

Texture2D::Texture2D(const char *texturePath, bool alpha) {
  stbi_set_flip_vertically_on_load(true);

  unsigned int format{GL_RGB};
  if (alpha) {
    format = GL_RGBA;
  }

  unsigned char *data{
      stbi_load(texturePath, &m_width, &m_height, &m_nrChannels, 0)};

  glGenTextures(1, &m_ID);
  glBindTexture(GL_TEXTURE_2D, m_ID);
  glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format,
               GL_UNSIGNED_BYTE, data);

  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
}

Texture2D::~Texture2D() { glDeleteTextures(1, &m_ID); }

void Texture2D::bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); }

unsigned int Texture2D::getID() const { return m_ID; }
