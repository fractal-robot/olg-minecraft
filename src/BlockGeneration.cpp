#include "BlockGeneration.h"
#include "blockEnum.h"
#include "constants.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility>

BlockGeneration::BlockGeneration(const std::string &jsonPath) {
  blocksVertices.reserve(static_cast<std::size_t>(blocksEnum::total));
  createBlocksList(jsonPath);
};

void BlockGeneration::createBlocksList(const std::string &jsonPath) {
  using json = nlohmann::json;

  std::ifstream file(jsonPath);
  if (!file.is_open())
    std::cerr << "BlockGeneration: unable to open json file.\n";

  json data;
  file >> data;

  float texWidth{1.f / static_cast<float>(data["texture_atlas"]["rows"])};
  float texHeight{1.f / static_cast<float>(data["texture_atlas"]["columns"])};

  int x, y;

  std::array<std::array<glm::vec2, 4>, 6> blockVertices;

  for (auto it{data["blocks"].begin()}; it != data["blocks"].end(); ++it) {
    int faceCounter{0};

    for (auto &face : it.value()) {
      x = static_cast<float>(face[0]);
      y = static_cast<float>(face[1]);

      blockVertices[faceCounter][0] = {x * texWidth, y * texHeight};
      blockVertices[faceCounter][1] = {x * texWidth + texWidth, y * texHeight};
      blockVertices[faceCounter][2] = {x * texWidth + texWidth,
                                       y * texHeight + texHeight};
      blockVertices[faceCounter][3] = {x * texWidth, y * texHeight + texHeight};

      ++faceCounter;
    }

    blocksVertices.push_back(blockVertices);
  }
}
