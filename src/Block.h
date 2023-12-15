#pragma once

#include "blockEnum.h"
#include <bitset>

class Block {
public:
  Block(blocksEnum block = blocksEnum::grass, bool active = true);
  ~Block();

  bool isActive() const;
  void setActive(bool active);

  blocksEnum getType() const;
  void setType(const blocksEnum block);
  void setType(const int block);

  std::bitset<6> Context{};

private:
  blocksEnum m_blockType;
  bool m_active;
};
