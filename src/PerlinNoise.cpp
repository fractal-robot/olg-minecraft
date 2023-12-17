#include "PerlinNoise.h"

#include "../libs/glm/vec2.hpp"
#include "constants.h"
#include <cmath>

HeightMap PerlinNoise::getNoise(int baseFrequency, int numberOctaves) {

  HeightMap map;

  for (int x{0}; x < constants::chunkSize; ++x) {
    for (int y{0}; y < constants::chunkSize; ++y) {
      float val{0};

      float freq{0};
      float amp{0};

      for (int i{0}; i < numberOctaves; ++i) {
        val += perlin(x * freq / baseFrequency, y * freq / baseFrequency) * amp;

        freq *= 2;
        amp /= 2;

        if (val > 1)
          val = 1;
        if (val < -1)
          val = -1;
      }

      map[x][y] = val;
    }
  }

  return map;
}

float PerlinNoise::perlin(float x, float y) {

  int x0 = static_cast<int>(x);
  int y0 = static_cast<int>(y);
  int x1 = x0 + 1;
  int y1 = y0 + 1;

  // interpolation weights
  float sx = x - static_cast<float>(x0);
  float sy = y - static_cast<float>(y0);

  // interpolate top corners
  float n0 = dotGridGradient(x0, y0, x, y);
  float n1 = dotGridGradient(x1, y0, x, y);
  float ix0 = interpolate(n0, n1, sx);

  // interpolate bottom corners
  n0 = dotGridGradient(x0, y1, x, y);
  n1 = dotGridGradient(x1, y1, x, y);
  float ix1 = interpolate(n0, n1, sx);

  // result
  return interpolate(ix0, ix1, sy);
}

float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y) {
  glm::vec2 gradient(randomGradient(ix, iy));

  // distance vectors
  float dx = x - static_cast<float>(ix);
  float dy = x - static_cast<float>(iy);

  // compute the dot product
  return (dx * gradient.x + dy * gradient.y);
}

glm::vec2 PerlinNoise::randomGradient(int ix, int iy) {
  const unsigned w = 8 * sizeof(unsigned);
  const unsigned s = w / 2;
  unsigned a = ix, b = iy;
  a *= 3284157443;

  b ^= a << s | a >> w - s;
  b *= 1911520717;

  a ^= b << s | b >> w - s;
  a *= 2048419325;
  float random = a * (3.14159265 / ~(~0u >> 1));

  return glm::vec2(sin(random), cos(random));
}

float PerlinNoise::interpolate(float a0, float a1, float weight) {
  return (a1 - a0) * (3. - weight * 2.) * weight * weight + a0;
}
