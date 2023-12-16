#pragma once

#include "../libs/glm/vec2.hpp"
#include "constants.h"
#include <array>
#include <map>
#include <string>
#include <vector>

class BlockGeneration {
public:
  std::vector<std::array<std::array<glm::vec2, 4>, 6>> blocksVertices;

  BlockGeneration(const std::string &jsonPath);

private:
  void createBlocksList(const std::string &jsonPath);
};
