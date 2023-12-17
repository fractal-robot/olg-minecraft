#pragma once

#include "Block.h"
#include "blockEnum.h"
#include "constants.h"
#include <array>
#include <bitset>
#include <vector>

class Chunk {
public:
  Chunk();
  ~Chunk();

  void update();
  void render() const;

private:
  std::array<
      std::array<std::array<Block, constants::chunkSize>, constants::chunkSize>,
      constants::chunkSize>
      m_chunk;

  std::vector<unsigned int> m_indices{};
  std::vector<float> m_vertices{};

  unsigned int m_VAO, m_VBO, m_EBO;
};
