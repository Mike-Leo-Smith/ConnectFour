//
// Created by Mike Smith on 2017/4/28.
//

#ifndef CONNECTFOUR_ALLOCATOR_H
#define CONNECTFOUR_ALLOCATOR_H

#include <cstdlib>

constexpr int MCT_NODE_MAX = 1000000000;

class MCTAllocator
{
private:
	void *_nodes;
	int _next;
	
	static MCTAllocator *_instance;
	static int _count;
	
	MCTAllocator(void);
	MCTAllocator(const MCTAllocator &) = delete;
	MCTAllocator &operator=(const MCTAllocator &) = delete;
	~MCTAllocator(void) { free(_nodes); }
	
public:
	void *alloc(size_t size);
	void reset(void);
	static MCTAllocator &instance(void) { return *_instance; }
	int count(void) const { return _count; }
};

#endif  // CONNECTFOUR_ALLOCATOR_H
