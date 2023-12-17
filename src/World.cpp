#include "World.h"
#include "../libs/glm/vec3.hpp"
#include "Chunck.h"
#include "constants.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <valarray>

World::World() {
  Chunck *ptr{new Chunck()};
  world[{0, 1, 0}] = ptr;
}

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

void World::reallocate(const glm::vec3 &pPos) {
  glm::ivec3 chunckPPos(pPos.x / constants::chunckSize,
                        pPos.y / constants::chunckSize,
                        pPos.z / constants::chunckSize);

  if (chunckPPos != m_oldChunckPPos) {

    for (const auto &e : world) {
      // eucledian distance formula
      if (std::sqrt(std::pow(e.first.x * constants::chunckSize - pPos.x, 2) +
                    std::pow(e.first.z * constants::chunckSize - pPos.z, 2)) <=
          constants::viewDistance) {
        if (world.find({e.first.x + 1, 0, e.first.z}) == world.end())
          world[{e.first.x + 1, 0, e.first.z}] = new Chunck;
        if (world.find({e.first.x - 1, 0, e.first.z}) == world.end())
          world[{e.first.x - 1, 0, e.first.z}] = new Chunck;
        if (world.find({e.first.x, 0, e.first.z + 1}) == world.end())
          world[{e.first.x, 0, e.first.z + 1}] = new Chunck;
        if (world.find({e.first.x, 0, e.first.z - 1}) == world.end())
          world[{e.first.x, 0, e.first.z - 1}] = new Chunck;
      } else {
        delete e.second;
        world.erase(e.first);
      }
    }
  }

  m_oldChunckPPos = chunckPPos;
}
