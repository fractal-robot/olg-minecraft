#include "World.h"
#include "../libs/glm/vec3.hpp"
#include "Chunck.h"
#include "constants.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
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
      //

      for (std::size_t x{0}; x < constants::viewDistance; ++x) {
        for (std::size_t z{0}; z < constants::viewDistance; ++z) {
          if (std::sqrt(std::pow(x * constants::chunckSize - pPos.x, 2) +
                        std::pow(z * constants::chunckSize - pPos.z, 2)) <=
              constants::viewDistance) {
            if (world.find({x, 0, z}) == world.end())
              world[{x, 0, z}] = new Chunck;
            if (world.find({-x, 0, z}) == world.end())
              world[{-x, 0, z}] = new Chunck;
            if (world.find({-x, 0, -z}) == world.end())
              world[{-x, 0, -z}] = new Chunck;
            if (world.find({x, 0, -z}) == world.end())
              world[{x, 0, -z}] = new Chunck;
          } else {
          }
        }
      }
    }
  }

  m_oldChunckPPos = chunckPPos;
}
