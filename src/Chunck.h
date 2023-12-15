#pragma once

#include "Block.h"
#include "constants.h"
#include <array>
#include <vector>

class Chunck {
public:
  Chunck();
  ~Chunck();

  void update();
  void render() const;
  void print() const;

private:
  std::array<std::array<std::array<Block, constants::chunckSize>,
                        constants::chunckSize>,
             constants::chunckSize>
      m_chunck;

  std::vector<unsigned int> m_indices{};
  std::vector<float> m_vertices{};

  unsigned int m_VAO, m_VBO, m_EBO;
};
