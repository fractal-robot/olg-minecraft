#include "ChunkManager.h"
#include "../libs/glm/vec3.hpp"
#include "Chunk.h"
#include "Shader.h"
#include "constants.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <valarray>
#include <vector>

World::World() {}

World::~World() {
  for (const auto &e : world) {
    delete e.second;
  }
}

void World::draw() const {
  for (const auto &e : world) {
    e.second->render();
  }
}

void World::update(const glm::vec3 &pPos, Shader &shader) {
  // using eucledian distance formula to determine if the chunck should be
  // created/removed/rendered

  for (int x{-constants::viewDistance}; x < constants::viewDistance; ++x) {
    for (int z{-constants::viewDistance}; z < constants::viewDistance; ++z) {
      if (std::sqrt(std::pow(x * constants::chunkSize - pPos.x, 2) +
                    std::pow(z * constants::chunkSize - pPos.z, 2)) <=
              constants::viewDistance &&
          world.find({x, 0, z}) == world.end()) {
        world[{x, 0, z}] = new Chunk;
      }
    }
  }

  std::vector<glm::ivec3> removeList;

  for (const auto &e : world) {
    if (std::sqrt(std::pow(e.first.x * constants::chunkSize - pPos.x, 2) +
                  std::pow(e.first.z * constants::chunkSize - pPos.z, 2)) <=
        constants::viewDistance) {

      glm::mat4 model{glm::mat4(1.0f)};
      model =
          glm::translate(model, glm::vec3(e.first.x * constants::chunkSize,
                                          e.first.y * constants::chunkSize,
                                          e.first.z * constants::chunkSize));
      shader.setMatrix4("model", model);
      e.second->render();
    } else {
      delete e.second;
      removeList.push_back(e.first);
    }
  }

  for (const auto &e : removeList) {
    world.erase(e);
  }
  removeList.clear();
}
