#pragma once

#include "constants.h"
#include <map>
#include <string>
#include <vector>

class BlockGeneration {
public:
  std::vector<float *> blocksVertexList;

  BlockGeneration(const std::string &jsonPath);
  ~BlockGeneration();

  unsigned int indices[constants::blockIndicesCount] = {
      // Front
      0, 1, 2, 2, 3, 0,
      // Back
      4, 5, 6, 6, 7, 4,
      // Left
      8, 9, 10, 10, 11, 8,
      // Right
      12, 13, 14, 14, 15, 12,
      // Top
      16, 17, 18, 18, 19, 16,
      // Bottom
      20, 21, 22, 22, 23, 20};

private:
  void createBlocksList(const std::string &jsonPath);

  float m_vertices[constants::blockVerticesCount] = {
      -0.5f, -0.5f, 0.5f,  .0f, .0f, 0.5f,  -0.5f, 0.5f,  .0f, .0f,
      0.5f,  0.5f,  0.5f,  .0f, .0f, -0.5f, 0.5f,  0.5f,  .0f, .0f,
      0.5f,  -0.5f, -0.5f, .0f, .0f, -0.5f, -0.5f, -0.5f, .0f, .0f,
      -0.5f, 0.5f,  -0.5f, .0f, .0f, 0.5f,  0.5f,  -0.5f, .0f, .0f,
      -0.5f, -0.5f, -0.5f, .0f, .0f, -0.5f, -0.5f, 0.5f,  .0f, .0f,
      -0.5f, 0.5f,  0.5f,  .0f, .0f, -0.5f, 0.5f,  -0.5f, .0f, .0f,
      0.5f,  -0.5f, 0.5f,  .0f, .0f, 0.5f,  -0.5f, -0.5f, .0f, .0f,
      0.5f,  0.5f,  -0.5f, .0f, .0f, 0.5f,  0.5f,  0.5f,  .0f, .0f,
      -0.5f, 0.5f,  0.5f,  .0f, .0f, 0.5f,  0.5f,  0.5f,  .0f, .0f,
      0.5f,  0.5f,  -0.5f, .0f, .0f, -0.5f, 0.5f,  -0.5f, .0f, .0f,
      -0.5f, -0.5f, -0.5f, .0f, .0f, 0.5f,  -0.5f, -0.5f, .0f, .0f,
      0.5f,  -0.5f, 0.5f,  .0f, .0f, -0.5f, -0.5f, 0.5f,  .0f, .0f};
};
