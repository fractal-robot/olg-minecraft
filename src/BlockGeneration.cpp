#include "BlockGeneration.h"
#include "constants.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility>

BlockGeneration::BlockGeneration(const std::string &jsonPath) {
  createBlocksList(jsonPath);
};

BlockGeneration::~BlockGeneration() {
  for (const auto &pair : blocksVertexList) {
    delete[] pair.second;
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

  for (auto it{data["blocks"].begin()}; it != data["blocks"].end(); ++it) {
    int faceCounter{0};

    for (auto &face : it.value()) {
      int faceElementsCounter{faceCounter *
                              (constants::blockVerticesCount / 6)};
      x = static_cast<float>(face[0]);
      y = static_cast<float>(face[1]);

      if (it.key() == "piston")
        std::cout << faceCounter << ": " << x * texWidth << ' ' << y * texWidth
                  << '\n'
                  << texWidth << '\n';

      m_vertices[(faceElementsCounter) + 3] = (x * texWidth);
      m_vertices[(faceElementsCounter) + 4] = (y * texHeight);
      m_vertices[(faceElementsCounter) + 8] = (x * texWidth) + texWidth;
      m_vertices[(faceElementsCounter) + 9] = (y * texHeight);
      m_vertices[(faceElementsCounter) + 13] = (x * texWidth) + texWidth;
      m_vertices[(faceElementsCounter) + 14] = (y * texHeight) + texHeight;
      m_vertices[(faceElementsCounter) + 18] = (x * texWidth);
      m_vertices[(faceElementsCounter) + 19] = (y * texHeight) + texHeight;

      ++faceCounter;
    }

    float *vertexArrayPointer{
        new float[static_cast<std::size_t>(constants::blockVerticesCount)]};
    std::copy(m_vertices, m_vertices + constants::blockVerticesCount,
              vertexArrayPointer);
    blocksVertexList.insert({it.key(), vertexArrayPointer});
    vertexArrayPointer = nullptr;

    int counter{1};
    if (it.key() == "piston") {
      for (auto &e : m_vertices) {
        std::cout << e << ' ';
        if (counter % 5 == 0) {
          std::cout << '\n';
        }
        ++counter;
      }
    }
  }
}
