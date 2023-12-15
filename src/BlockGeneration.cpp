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

void BlockGeneration::print() const {

  for (std::size_t i{0}; i < constants::blockVerticesCount; ++i) {
    std::cout
        << blocksVertexList[static_cast<std::size_t>(blocksEnum::grass)][i]
        << ' ';
  }

  std::cout << '\n' << '\n';
}

BlockGeneration::BlockGeneration(const std::string &jsonPath) {
  blocksVertexList.reserve(static_cast<std::size_t>(blocksEnum::total));

  blocksVertices.reserve(static_cast<std::size_t>(blocksEnum::total));
  createBlocksList(jsonPath);
};

BlockGeneration::~BlockGeneration() {
  for (const auto &ptr : blocksVertexList) {
    delete[] ptr;
  }
}

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
      int faceElementsCounter{faceCounter *
                              (constants::blockVerticesCount / 6)};
      x = static_cast<float>(face[0]);
      y = static_cast<float>(face[1]);

      m_vertices[(faceElementsCounter) + 3] = (x * texWidth);
      m_vertices[(faceElementsCounter) + 4] = (y * texHeight);
      m_vertices[(faceElementsCounter) + 8] = (x * texWidth) + texWidth;
      m_vertices[(faceElementsCounter) + 9] = (y * texHeight);
      m_vertices[(faceElementsCounter) + 13] = (x * texWidth) + texWidth;
      m_vertices[(faceElementsCounter) + 14] = (y * texHeight) + texHeight;
      m_vertices[(faceElementsCounter) + 18] = (x * texWidth);
      m_vertices[(faceElementsCounter) + 19] = (y * texHeight) + texHeight;

      blockVertices[faceCounter][0] = {x * texWidth, y * texHeight};
      blockVertices[faceCounter][1] = {x * texWidth + texWidth, y * texHeight};
      blockVertices[faceCounter][2] = {x * texWidth + texWidth,
                                       y * texHeight + texHeight};
      blockVertices[faceCounter][3] = {x * texWidth, y * texHeight + texHeight};

      ++faceCounter;
    }

    blocksVertices.push_back(blockVertices);

    float *vertexArrayPointer{
        new float[static_cast<std::size_t>(constants::blockVerticesCount)]};
    std::copy(m_vertices, m_vertices + constants::blockVerticesCount,
              vertexArrayPointer);
    blocksVertexList.push_back(vertexArrayPointer);
    vertexArrayPointer = nullptr;
  }
}
