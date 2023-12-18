
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

		//// Alpha-beta pruning
		if (score > alpha) {
			alpha = score;
		}

		if (alpha >= beta) {
			break;
		}
	}

	return bestScore;
};


/*
*@param (flag) get the best move minimax algorithm with alpha-beta pruning for the AI
*/
void findBestMoveAlphaBeta(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth, int bestMove[2]) {
	int opponent = (player == 1) ? 2 : 1;
	int bestScore = -1000000;

	int moves[BOARD_SIZE * BOARD_SIZE][2];
	int movesCount = 0;

	//// Get all valid moves
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (isValidMove(board, x, y, player)) {
				moves[movesCount][0] = x;
				moves[movesCount][1] = y;
				movesCount++;
			}
		}
	}

	//// Make the best move for the AI
	for (int i = 0; i < movesCount; i++) {
		int x = moves[i][0];
		int y = moves[i][1];

		int newBoard[BOARD_SIZE][BOARD_SIZE];
		memcpy(newBoard, board, sizeof(newBoard));

		makeMove(newBoard, x, y, player);

		int score = -alphabeta(newBoard, opponent, depth - 1, -1000000, 1000000);

		if (score > bestScore) {
			bestScore = score;
			bestMove[0] = x;
			bestMove[1] = y;
		}
	}
};
