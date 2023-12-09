#pragma once

#include <string>
class Block {
public:
  Block(const std::string &blockName);
  void getDescription();

private:
  float m_vertices[120] = {
      // Front
      -0.5f, -0.5f, 0.5f, .0f, .0f, 0.5f, -0.5f, 0.5f, .0f, .0f, 0.5f, 0.5f,
      0.5f, .0f, .0f, -0.5f, 0.5f, 0.5f, .0f, .0f,
      // Back
      0.5f, -0.5f, -0.5f, .0f, .0f, -0.5f, -0.5f, -0.5f, .0f, .0f, -0.5f, 0.5f,
      -0.5f, .0f, .0f, 0.5f, 0.5f, -0.5f, .0f, .0f,
      // Left
      -0.5f, -0.5f, -0.5f, .0f, .0f, -0.5f, -0.5f, 0.5f, .0f, .0f, -0.5f, 0.5f,
      0.5f, .0f, .0f, -0.5f, 0.5f, -0.5f, .0f, .0f,
      // Right
      0.5f, -0.5f, 0.5f, .0f, .0f, 0.5f, -0.5f, -0.5f, .0f, .0f, 0.5f, 0.5f,
      -0.5f, .0f, .0f, 0.5f, 0.5f, 0.5f, .0f, .0f,
      // Top
      -0.5f, 0.5f, 0.5f, .0f, .0f, 0.5f, 0.5f, 0.5f, .0f, .0f, 0.5f, 0.5f,
      -0.5f, .0f, .0f, -0.5f, 0.5f, -0.5f, .0f, .0f,
      // Bottom
      -0.5f, -0.5f, -0.5f, .0f, .0f, 0.5f, -0.5f, -0.5f, .0f, .0f, 0.5f, -0.5f,
      0.5f, .0f, .0f, -0.5f, -0.5f, 0.5f, .0f, .0f};

  unsigned int m_indices[36] = { // Front
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
};
