//
// Created by Mike Smith on 2017/4/28.
//

#include "node.h"

void *MCTNode::operator new(size_t size)
{
	MCTAllocator &allocator = MCTAllocator::instance();
	return allocator.alloc(size);
}

void *MCTNode::operator new[](size_t size)
{
	MCTAllocator &allocator = MCTAllocator::instance();
	return allocator.alloc(size);
}

MCTNode::MCTNode(MCTNode *f, const Game &g) : father(f), game(g), win(0), total(0)
{
	for (int i = 0; i < 12; i++)
	{
		children[i] = nullptr;
	}
}
