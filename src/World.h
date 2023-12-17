#pragma once

#include <functional>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include "../libs/glm/gtx/hash.hpp"

#include "../libs/glm/vec3.hpp"
#include "Chunck.h"
#include <unordered_map>

class World {

public:
  std::unordered_map<glm::ivec3, Chunck *> world;

  World();
  ~World();
  void draw() const;
  void reallocate(const glm::vec3 &pPos);

private:
  glm::ivec3 m_oldChunckPPos;
};
