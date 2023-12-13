#include "Mesher.h"
#include "blockEnum.h"
#include "constants.h"
#include <algorithm>
#include <cstddef>

BlockGeneration blockVertex("../../res/textures/block_info.json");

void Mesher::mesh(ChunckArray &chunck, unsigned int (&indices)[1000],

                  float (&vertices)[10000]) {

  std::array<unsigned int, 10000> templateIndices = {// Front
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

  std::array<float, 100000> templateVertices = {
      -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
      -0.5f, 0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
      -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f,
      0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
      0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
      0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,
  };

  std::size_t verticesCounter{0};
  std::size_t indicesCounter{0};

  for (std::size_t x{0}; x < constants::chunckSize; ++x) {
    for (std::size_t y{0}; y < constants::chunckSize; ++y) {
      for (std::size_t z{0}; z < constants::chunckSize; ++z) {

        if (!chunck[x][y][z].isActive()) {
          continue;
        }

        // set block vertices
        for (std::size_t faceCounter{0}; faceCounter < 6; ++faceCounter) {
          for (std::size_t vertexCounter{0}; vertexCounter < 4;
               ++vertexCounter) {
            // coordinates
            vertices[verticesCounter] = templateVertices[faceCounter * 3] / x;
            ++verticesCounter;
            vertices[verticesCounter] =
                templateVertices[faceCounter * 3 + 1] / y;
            ++verticesCounter;
            vertices[verticesCounter] =
                templateVertices[faceCounter * 3 + 2] / z;
            ++verticesCounter;

            // uv coordinates
            std::size_t blockType =
                static_cast<std::size_t>(chunck[x][y][z].getType());

            vertices[verticesCounter] =
                blockVertex
                    .blocksVertices[blockType][faceCounter][vertexCounter]
                    .x;
            ++verticesCounter;

            vertices[verticesCounter] =
                blockVertex
                    .blocksVertices[blockType][faceCounter][vertexCounter]
                    .y;

            ++verticesCounter;
          }
        }

        // set block indices
        std::for_each(templateIndices.begin(), templateIndices.end(),
                      [](unsigned int &n) { n += 6 * 4; });
        std::copy(templateIndices.begin(), templateIndices.end(),
                  indices + indicesCounter * 6 * 6);

        ++indicesCounter;
      }
    }
  }
}
