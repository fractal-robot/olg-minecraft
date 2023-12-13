#pragma once

#include "Block.h"
#include "constants.h"
#include <array>

class Chunck {
public:
  Chunck();
  ~Chunck();

  void update();
  void render() const;

private:
  std::array<std::array<std::array<Block, constants::chunckSize>,
                        constants::chunckSize>,
             constants::chunckSize>
      m_chunck;

  unsigned int m_indices[1000];
  float m_vertices[10000];

  unsigned int m_VAO, m_VBO, m_EBO;
};
