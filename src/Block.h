#pragma once

#include "blockEnum.h"
#include <bitset>

struct Block {
  std::bitset<6> context{};
  blocksEnum type;
  bool active;

  Block(blocksEnum block = blocksEnum::grass, bool active = true)
      : type(block), active(active){};
};
