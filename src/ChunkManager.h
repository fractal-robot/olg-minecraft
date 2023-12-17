#pragma once

#include <functional>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include "../libs/glm/gtx/hash.hpp"

#include "../libs/glm/vec3.hpp"
#include "Chunk.h"
#include "Shader.h"
#include <unordered_map>

class World {

public:
  std::unordered_map<glm::ivec3, Chunk *> world;

  World();
  ~World();
  void draw() const;
  void update(const glm::vec3 &pPos, Shader &shader);

private:
  glm::ivec3 m_oldChunkPPos;
};
