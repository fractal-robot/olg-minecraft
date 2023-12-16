#include "Mesher.h"
#include "blockEnum.h"
#include "constants.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

BlockGeneration blockVertex("../../res/textures/block_info.json");

void Mesher::mesh(ChunckArray &chunck, std::vector<float> &vertices,
                  std::vector<unsigned int> &indices) {

  std::array<unsigned int, 36> templateIndices = {// Front
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

  std::array templateVertices = {
      -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
      -0.5f, 0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
      -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f,
      0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
      0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
      0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,
  };

  std::size_t indicesCounter{0};

  for (std::size_t x{0}; x < constants::chunckSize; ++x) {
    for (std::size_t y{0}; y < constants::chunckSize; ++y) {
      for (std::size_t z{0}; z < constants::chunckSize; ++z) {

        if (!chunck[x][y][z].isActive()) {
          continue;
        }

        if (x == 0)
          chunck[x][y][z].setType(blocksEnum::magma);

        if (y == 0)
          chunck[x][y][z].setType(blocksEnum::redstone_block);

        if (z == 0)
          chunck[x][y][z].setType(blocksEnum::bedrock);

        if (z + 1 == constants::chunckSize || !chunck[x][y][z + 1].isActive())
          chunck[x][y][z].Context.set(5);
        if (z == 0 || !chunck[x][y][z - 1].isActive())
          chunck[x][y][z].Context.set(4);

        if (x == 0 || !chunck[x - 1][y][z].isActive())
          chunck[x][y][z].Context.set(3);
        if (x + 1 == constants::chunckSize || !chunck[x + 1][y][z].isActive())
          chunck[x][y][z].Context.set(2);

        if (y + 1 == constants::chunckSize || !chunck[x][y + 1][z].isActive())
          chunck[x][y][z].Context.set(1);
        if (y == 0 || !chunck[x][y - 1][z].isActive())
          chunck[x][y][z].Context.set(0);

        // set block vertices
        for (std::size_t faceCounter{0}; faceCounter < 6; ++faceCounter) {
          if (chunck[x][y][z].Context.test(5 - faceCounter)) {
            for (std::size_t vertexCounter{0}; vertexCounter < 4;
                 ++vertexCounter) {
              vertices.push_back(
                  templateVertices[vertexCounter * 3 + faceCounter * 12] + x);
              vertices.push_back(
                  templateVertices[vertexCounter * 3 + faceCounter * 12 + 1] +
                  y);
              vertices.push_back(
                  templateVertices[vertexCounter * 3 + faceCounter * 12 + 2] +
                  z);

              std::size_t blockType =
                  static_cast<std::size_t>(chunck[x][y][z].getType());

              vertices.push_back(
                  blockVertex
                      .blocksVertices[blockType][faceCounter][vertexCounter]
                      .x);

              vertices.push_back(
                  blockVertex
                      .blocksVertices[blockType][faceCounter][vertexCounter]
                      .y);
            }
          }
        }

        indices.insert(indices.end(), templateIndices.begin(),
                       templateIndices.end());

        // set block indices
        std::for_each(templateIndices.begin(), templateIndices.end(),
                      [](unsigned int &n) { n += 6 * 4; });

        ++indicesCounter;
      }
    }
  }
}
