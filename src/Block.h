#pragma once

#include "blockEnum.h"

class Block {
public:
  Block(blocksEnum block = blocksEnum::grass, bool active = true);
  ~Block();

  bool isActive() const;
  void setActive(bool active);

  blocksEnum getType() const;
  void setType(const blocksEnum block);
  void setType(const int block);

private:
  blocksEnum m_blockType;
  bool m_active;
};
