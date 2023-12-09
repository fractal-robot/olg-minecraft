#pragma once

#include <string>
class Texture2D {

public:
  Texture2D(const char *texturePath, bool alpha);
  ~Texture2D();
  void bind() const;
  unsigned int getID() const;

private:
  unsigned int m_ID;
  int m_width, m_height, m_nrChannels;
};
