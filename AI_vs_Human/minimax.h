
#ifndef MINIMAX_H
#define MINIMAX_H

#include "game.h"

int minimax(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth);
void findBestMoveMinimax(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth, int bestMove[2]);

#endif
