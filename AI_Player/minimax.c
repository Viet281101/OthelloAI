
#include "minimax.h"


/*
*@param (flag) minimax algorithm wihout alpha-beta pruning
*/
int minimax(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth) {
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

		int score = -minimax(newBoard, opponent, depth - 1);

		if (score > bestScore) {
			bestScore = score;
		}
	}

	return bestScore;
};
