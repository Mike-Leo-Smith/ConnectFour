#include <iostream>
#include <cmath>
#include "Game/game.h"
#include "MCTS/node.h"
#include "MCTS/tree.h"
#include "Clock/clock.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main()
{
	Game game;
	MCT tree;
	
	while (true)
	{
		game.reset(10, 10, 0);
		while (true)
		{
			Clock clock;
			
			int max_col = 0;
			double q_max = 0;
			double q[game.cols()];
			
			clock.reset();
			
			for (int i = 0; i < game.cols(); i++)
			{
				q[i] = 0;
			}
			
			for (int iter = 0; iter < 20000; iter++)
			{
				for (int i = 0; i < game.cols(); i++)
				{
					Game game_copy = game;
					
					if (!game_copy.column_full(i))
					{
						game_copy.place_piece(i);
						q[i] += tree.default_policy(game_copy);
					}
					else
					{
						q[i] = -10;
					}
				}
			}
			
			for (int i = 0; i < game.cols(); i++)
			{
				if (q[i] >= q_max)
				{
					q_max = q[i];
					max_col = i;
				}
			}
			
			std::cout << max_col << std::endl;
			std::cout << clock.tick() << "ms" << std::endl;
			game.place_piece(max_col);
			game.print();
			if (game.status() != IN_GAME)
			{
				break;
			}
			
			int col = 0;
			
			clock.reset();
			col = tree.uct_search(game, 3000);
			std::cout << col << std::endl;
			std::cout << clock.tick() << "ms" << std::endl;
			game.place_piece(col);
			game.print();
			if (game.status() != IN_GAME)
			{
				break;
			}
		}
		
		std::cout << "Player " << game.status() << " wins" << std::endl;
	}
	return 0;
}

#pragma clang diagnostic pop