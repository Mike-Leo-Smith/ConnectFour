//
// Created by Mike Smith on 2017/4/28.
//

#include "allocator.h"
#include "node.h"

MCTAllocator *MCTAllocator::_instance = new MCTAllocator;
int MCTAllocator::_count = 0;

void *MCTAllocator::alloc(size_t size)
{
	if (_next + size < MCT_NODE_MAX)
	{
		void *node = (char *)_nodes + _next;
		
		_next += size;
		_count++;
		return node;
	}
	else
	{
		return nullptr;
	}
}

MCTAllocator::MCTAllocator(void) : _next(0)
{
	_nodes = malloc(MCT_NODE_MAX * sizeof(MCT_NODE_MAX));
}

void MCTAllocator::reset(void)
{
	_next = 0;
	_count = 0;
	//memset(_nodes, 0, MCT_NODE_MAX * sizeof(MCT_NODE_MAX));
}
