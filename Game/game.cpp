//
// Created by Mike Smith on 2017/4/28.
//

#include <cstring>
#include <iostream>
#include "game.h"

void Game::reset(int rows, int cols, int first_player)
{
	_rows = rows;
	_cols = cols;
	_player = first_player;
	for (int i = 0; i < 12; i++)
	{
		_board[0][i] = _board[1][i] = 0;
	}
	_status = IN_GAME;
	_bad_row = rand() % _rows;
	_bad_col = rand() % _cols;
}

int Game::available_row(int col) const
{
	Column occupied = _board[0][col] | _board[1][col];  // Gather all pieces in the column.
	
	if (col == _bad_col)
	{
		occupied |= (1 << _bad_row);
	}
	
	// Check from bottom.
	for (int i = 0; i < _rows; i++)
	{
		if ((occupied & 1) == 0)
		{
			return i;
		}
		occupied >>= 1;
	}
	
	return -1;
}

int Game::place_piece(int col)
{
	int row = available_row(col);
	
	if (row != -1)
	{
		_board[_player][col] |= (1 << row);
		_update_status(row, col);
		_player ^= 1;
	}
	
	return row;
}

void Game::_update_status(int last_row, int last_col)
{
	// Vertical.
	Column column = _board[_player][last_col];
	
	if (column & (column >> 1) & (column >> 2) & (column >> 3))
	{
		_status = _player;
		return;
	}
	
	int min_col = (last_col >= 3 ? last_col - 3 : 0);
	int max_col = (last_col + 3 < _cols ? last_col + 3 : _cols);
	
	int d = max_col - min_col - 2;
	
	for (int i = 0; i < d; i++)
	{
		Column c1 = _board[_player][min_col + i];
		Column c2 = _board[_player][min_col + i + 1];
		Column c3 = _board[_player][min_col + i + 2];
		Column c4 = _board[_player][min_col + i + 3];
		
		// Horizontal.
		if (c1 & c2 & c3 & c4)
		{
			_status = _player;
			return;
		}
		
		// Diagonal.
		if ((c1 & (c2 >> 1) & (c3 >> 2) & (c4 >> 3)) || (c1 & (c2 << 1) & (c3 << 2) & (c4 << 3)))
		{
			_status = _player;
			return;
		}
	}
	
	for (int col = 0; col < _cols; col++)
	{
		Column c = _board[0][col] | _board[1][col];
		
		if (_bad_row == _rows - 1 && col == _bad_col)
		{
			c |= (1 << _bad_row);
		}
		
		if ((c & (1 << (_rows - 1))) == 0)
		{
			_status = IN_GAME;
			return;
		}
	}
	
	_status = TIE;
	return;
}

void Game::print(void)
{
	for (int col = 0; col < _cols; col++)
	{
		std::cout << (col < 10 ? " " : "") << col;
	}
	std::cout << std::endl;
	
	for (int row = _rows - 1; row >= 0; row--)
	{
		std::cout << "|";
		for (int col = 0; col < _cols; col++)
		{
			if (row == _bad_row && col == _bad_col)
			{
				std::cout << "X|";
			}
			else if (_board[0][col] & (1 << row))
			{
				std::cout << "O|";
			}
			else if (_board[1][col] & (1 << row))
			{
				std::cout << "#|";
			}
			else
			{
				std::cout << "_|";
			}
		}
		std::cout << std::endl;
	}
}

bool Game::column_full(int col) const
{
	Column column = _board[0][col] | _board[1][col];
	
	if (col == _bad_col)
	{
		column |= (1 << _bad_row);
	}
	
	return (bool)(column & (1 << _rows));
}
