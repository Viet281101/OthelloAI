
#include "game.h"
#include "minimax.h"
#include "alphabeta.h"


int copyBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]) {
	for (int x = 0; x < BOARD_SIZE; x++) {
		memcpy(newBoard[x], board[x], BOARD_SIZE * sizeof(int));
	}

	return 0;
};


int evaluateBoard(int board[BOARD_SIZE][BOARD_SIZE], int player) {
	int opponent = (player == 1) ? 2 : 1;
	int score = 0;

	//// Corners
	if (board[0][0] == player) score += 100;
	if (board[0][0] == opponent) score -= 100;
	if (board[0][BOARD_SIZE - 1] == player) score += 100;
	if (board[0][BOARD_SIZE - 1] == opponent) score -= 100;
	if (board[BOARD_SIZE - 1][0] == player) score += 100;
	if (board[BOARD_SIZE - 1][0] == opponent) score -= 100;
	if (board[BOARD_SIZE - 1][BOARD_SIZE - 1] == player) score += 100;
	if (board[BOARD_SIZE - 1][BOARD_SIZE - 1] == opponent) score -= 100;

	//// Stability
	int stability[BOARD_SIZE][BOARD_SIZE] = {
		{ 100, -20, 10,  5,  5, 10, -20, 100 },
		{ -20, -50, -2, -2, -2, -2, -50, -20 },
		{  10,  -2, -1, -1, -1, -1,  -2,  10 },
		{   5,  -2, -1, -1, -1, -1,  -2,   5 },
		{   5,  -2, -1, -1, -1, -1,  -2,   5 },
		{  10,  -2, -1, -1, -1, -1,  -2,  10 },
		{ -20, -50, -2, -2, -2, -2, -50, -20 },
		{ 100, -20, 10,  5,  5, 10, -20, 100 }
	};

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (board[x][y] == player) {
				score += stability[x][y];
			} else if (board[x][y] == opponent) {
				score -= stability[x][y];
			}
		}
	}

	//// Mobility
	int playerMoves = 0;
	int opponentMoves = 0;

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (isValidMove(board, x, y, player)) {
				playerMoves++;
			} else if (isValidMove(board, x, y, opponent)) {
				opponentMoves++;
			}
		}
	}

	if (playerMoves > opponentMoves) {
		score += (100 * playerMoves) / (playerMoves + opponentMoves);
	} else if (playerMoves < opponentMoves) {
		score -= (100 * opponentMoves) / (playerMoves + opponentMoves);
	}

	//// Pieces
	int playerPieces = 0;
	int opponentPieces = 0;

	countPieces(board, &playerPieces, &opponentPieces);

	if (playerPieces > opponentPieces) {
		score += (100 * playerPieces) / (playerPieces + opponentPieces);
	} else if (playerPieces < opponentPieces) {
		score -= (100 * opponentPieces) / (playerPieces + opponentPieces);
	}

	return score;
};


void testAI () {
	int board[BOARD_SIZE][BOARD_SIZE] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // 0
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // 1
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // 2
		{ 0, 0, 0, 1, 2, 0, 0, 0 }, // 3
		{ 0, 0, 0, 2, 1, 0, 0, 0 }, // 4
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // 5
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // 6
		{ 0, 0, 0, 0, 0, 0, 0, 0 }  // 7
	};

	int player = 1;
	int depth = 5;
	int alpha = -1000000;
	int beta = 1000000;

	int minimaxScore = minimax(board, player, depth, alpha, beta);
	int alphabetaScore = alphabeta(board, player, depth, alpha, beta);

	printf("Minimax score: %d\n", minimaxScore);
	printf("Alphabeta score: %d\n", alphabetaScore);
};

