
#include "alphabeta.h"


/*
*@param (flag) minimax algorithm with alpha-beta pruning to improve the performance
*/
int alphabeta(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth, int alpha, int beta) {
	int opponent = (player == 1) ? 2 : 1;

	if (depth == 0 || isGameOver(board)) {
		return evaluateBoard(board, player);
	}

	int moves[BOARD_SIZE * BOARD_SIZE][2];
	int movesCount = 0;

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (isValidMove(board, x, y, player)) {
				moves[movesCount][0] = x;
				moves[movesCount][1] = y;
				movesCount++;
			}
		}
	}

	if (movesCount == 0) {
		return evaluateBoard(board, player);
	}

	int bestScore = -1000000;

	for (int i = 0; i < movesCount; i++) {
		int x = moves[i][0];
		int y = moves[i][1];

		int newBoard[BOARD_SIZE][BOARD_SIZE];
		memcpy(newBoard, board, sizeof(newBoard));

		makeMove(newBoard, x, y, player);

		int score = -alphabeta(newBoard, opponent, depth - 1, -beta, -alpha);

		if (score > bestScore) {
			bestScore = score;
		}

		if (score > alpha) {
			alpha = score;
		}

		if (alpha >= beta) {
			break;
		}
	}

	return bestScore;
};