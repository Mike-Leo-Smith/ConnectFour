//
// Created by Mike Smith on 2017/4/28.
//

#ifndef CONNECTFOUR_TREE_H
#define CONNECTFOUR_TREE_H

#include "../Game/game.h"
#include "allocator.h"
#include "node.h"

class MCT
{
private:
	MCTAllocator &_allocator;
	
	MCTNode *tree_policy(MCTNode *node);
	MCTNode *expand(MCTNode *node, int child_index);
	MCTNode *best_child(MCTNode *node, double c);
	int best_child_index(MCTNode *node, double c);
	
public:
	MCT(void) : _allocator(MCTAllocator::instance()) {}
	int uct_search(const Game &game, time_t time);
	double default_policy(const Game &game) const;
};

#endif  // CONNECTFOUR_TREE_H
