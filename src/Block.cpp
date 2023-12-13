#include "Block.h"
#include "blockEnum.h"

Block::Block(blocksEnum block, bool active)
    : m_blockType(block), m_active(active) {}

Block::~Block(){};

blocksEnum Block::getType() const { return m_blockType; };

bool Block::isActive() const { return m_active; }

void Block::setType(const blocksEnum block) { m_blockType = block; }
void Block::setType(const int block) {
  m_blockType = static_cast<blocksEnum>(block);
};
