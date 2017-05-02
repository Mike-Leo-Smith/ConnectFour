//
// Created by Mike Smith on 2017/4/28.
//

#ifndef CONNECTFOUR_GAME_H
#define CONNECTFOUR_GAME_H

#include <cstdint>

typedef uint_fast16_t Column;   // A 64-bit unsigned integer represents four columns in the board.

enum GameStatus
{
	WIN_0,
	WIN_1,
	TIE,
	IN_GAME
};

class Game
{
private:
	Column _board[2][12];       // Here _board[0] for player 0, _board[1] for player 1.
	int _bad_row;
	int _bad_col;               // Place in the board where cannot be placed pieces.
	int _player;                // Value of _player should be either 0 or 1.
	int _rows;
	int _cols;                  // Size of the board.
	int _status;                // Game status.
	
	void _update_status(int last_row, int last_col);
	
public:
	void reset(int rows, int cols, int first_player);
	int status(void) const { return _status; }
	int cols(void) const { return _cols; }
	int rows(void) const { return _rows; }
	bool column_full(int col) const;
	int player(void) const { return _player; }
	int available_row(int col) const;
	int place_piece(int col);
	void print(void);
};

#endif  // CONNECTFOUR_GAME_H
