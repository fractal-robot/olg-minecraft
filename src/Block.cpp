#include "Block.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

Block::Block(const std::string &blockName, const std::string &jsonPath)
    : m_blockName(blockName), m_jsonPath(jsonPath){};

void Block::parseBlockProp() {
  using json = nlohmann::json;

  std::ifstream file(m_jsonPath);
  if (!file.is_open())
    std::cerr << "Block: unable to open json file.";

  json data;
  file >> data;

  float texWidth{1.f / static_cast<float>(data["texture_atlas"]["rows"])};
  float texHeight{1.f / static_cast<float>(data["texture_atlas"]["columns"])};

  int faceCounter;

  auto blocksData = data["blocks"];
  for (auto face : blocksData[m_blockName]) {
    int faceElementsCounter{faceCounter * 20}; // * 4 * 5

    m_vertices[(faceElementsCounter) + 03] = (x * width) + 0.0f;
    m_vertices[(faceElementsCounter) + 04] = (y * height) + 0.0f;
    m_vertices[(faceElementsCounter) + 08] = (x * width) + width;
    m_vertices[(faceElementsCounter) + 09] = (y * height) + 0.0f;
    m_vertices[(faceElementsCounter) + 13] = (x * width) + width;
    m_vertices[(faceElementsCounter) + 14] = (y * height) + width;
    m_vertices[(faceElementsCounter) + 18] = (x * width) + 0.0f;
    m_vertices[(faceElementsCounter) + 19] = (y * height) + width;

    ++faceCounter;
  }
}
