//
// Created by Mike Smith on 2017/4/28.
//

#include <cmath>
#include "tree.h"
#include "../Clock/clock.h"

constexpr double INF = 1e60;

int MCT::uct_search(const Game &game, time_t time)
{
	_allocator.reset();
	
	Clock clock;
	MCTNode *root = new MCTNode(nullptr, game);
	
	clock.reset();
	while (clock.tick() < time)
	{
		MCTNode *node = tree_policy(root);
		double delta = default_policy(node->game);
		
		// Backup
		while (node != nullptr)
		{
			node->total++;
			node->win += delta;
			delta = -delta;
			node = node->father;
		}
	}
	std::cout << _allocator.count() << " nodes created." << std::endl;
	return best_child_index(root, 0);
}

inline MCTNode *MCT::tree_policy(MCTNode *node)
{
	while (node->game.status() == IN_GAME)
	{
		for (int i = 0; i < node->game.cols(); i++)
		{
			if (node->children[i] == nullptr && !node->game.column_full(i))
			{
				return expand(node, i);
			}
		}
		
		node = best_child(node, 2);
	}
	
	return node;
}

inline MCTNode *MCT::expand(MCTNode *node, int child_index)
{
	MCTNode *child = new MCTNode(node, node->game);
	
	node->children[child_index] = child;
	
	child->game.place_piece(child_index);
	child->win = default_policy(child->game);
	child->total = 1;
	
	return child;
}

inline MCTNode *MCT::best_child(MCTNode *node, double c)
{
	return node->children[best_child_index(node, c)];
}

inline int MCT::best_child_index(MCTNode *node, double c)
{
	int best_index = 0;
	double best_confidence = -INF;
	
	for (int i = 0; i < node->game.cols(); i++)
	{
		MCTNode *child = node->children[i];
		
		if (child != nullptr)
		{
			double confidence = child->win / (double)child->total + c * sqrt(2 * log(node->total) / child->total);
			if (c == 0) std::cout << confidence << " ";
			
			if (confidence >= best_confidence)
			{
				best_confidence = confidence;
				best_index = i;
			}
		}
	}
	
	if (c == 0)
	{
		std::cout << std::endl;
		for (int i = 0; i < node->game.cols(); i++)
		{
			std::cout << "(" << node->children[i]->win << ", " << node->children[i]->total << ") ";
		}
		std::cout << std::endl;
	}
	
	return best_index;
}

double MCT::default_policy(const Game &game) const
{
	// End of a game.
	if (game.status() != IN_GAME)
	{
		return (game.status() != game.player());
	}
	
	int parent_lose = 0;
	constexpr int iterations = 10;
	
	for (int i = 0; i < iterations; i++)
	{
		Game game_copy = game;
		
		while (game_copy.status() == IN_GAME)
		{
			game_copy.place_piece(rand() % game_copy.cols());
		}
		
		if (game_copy.status() == game.player())
		{
			parent_lose++;
		}
	}
	
	return 1.0 - parent_lose / (double)iterations;
}
