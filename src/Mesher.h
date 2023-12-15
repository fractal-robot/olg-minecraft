#pragma once

#include "Block.h"
#include "BlockGeneration.h"
#include "constants.h"
#include <array>
#include <vector>

using ChunckArray = std::array<
    std::array<std::array<Block, constants::chunckSize>, constants::chunckSize>,
    constants::chunckSize>;

using BlocksTexVertices = std::vector<std::array<std::array<glm::vec2, 4>, 6>>;

class Mesher {
public:
  static void mesh(ChunckArray &chunck, std::vector<float> &vertices,
                   std::vector<unsigned int> &indices);
};
