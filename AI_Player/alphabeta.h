
#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "game.h"

int alphabeta(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth, int alpha, int beta);
void findBestMoveAlphaBeta(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth, int bestMove[2]);

#endif
