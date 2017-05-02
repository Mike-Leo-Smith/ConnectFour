//
// Created by Mike Smith on 2017/4/28.
//

#ifndef CONNECTFOUR_NODE_H
#define CONNECTFOUR_NODE_H

#include <iostream>
#include "allocator.h"
#include "../Game/game.h"

struct MCTNode
{
	double win;
	int total;
	MCTNode *father;
	MCTNode *children[12];
	Game game;
	
	MCTNode(MCTNode *father, const Game &g);
	
	static void *operator new(size_t size);
	static void *operator new[](size_t size);
	static void operator delete(void *) {}
	static void operator delete[](void *) {}
};

#endif  // CONNECTFOUR_NODE_H
