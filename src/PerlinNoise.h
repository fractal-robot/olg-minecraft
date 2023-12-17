#pragma once

#include "../libs/glm/vec2.hpp"
#include "constants.h"
#include <array>

using HeightMap =
    std::array<std::array<float, constants::chunkSize>, constants::chunkSize>;

class PerlinNoise {
public:
  HeightMap getNoise(int baseFrequency, int numberOctaves);
  // sample the value of the noise at the given coordinate

private:
  float perlin(float x, float y);
  float dotGridGradient(int ix, int iy, float x, float y);
  glm::vec2 randomGradient(int ix, int iy);
  float interpolate(float a0, float a1, float weight);
};
