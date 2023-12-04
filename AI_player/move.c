
#include "game.h"


/*
*@param (flag) check a line in a direction (dx, dy) to see if it is valid or not
*/
bool checkDirection(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int dx, int dy, int player) {
	int opponent = player == 1 ? 2 : 1;
	int count = 0;

	while (true) {
		x += dx;
		y += dy;

		if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) return false;

		if (board[x][y] == opponent) {
			count++;
		} else if (board[x][y] == player) {
			return count > 0;
		} else {
			return false;
		}
	}
};

/*
*@param (flag) check if the move is valid or not (return true/false)
*/
bool isValidMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
	if (board[x][y] != 0) return false;

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if ((dx != 0 || dy != 0) && checkDirection(board, x, y, dx, dy, player)) {
				return true;
			}
		}
	}

	return false;
};

/*
*@param (flag) make the move on the board
*/
void makeMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
	board[x][y] = player;
	int opponent = (player == 1) ? 2 : 1;

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0) continue;

			int nx = x + dx;
			int ny = y + dy;
			int piecesToFlip = 0;

			while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] == opponent) {
				piecesToFlip++;
				nx += dx;
				ny += dy;
			}

			if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] == player && piecesToFlip > 0) {
				while (piecesToFlip-- > 0) {
					nx -= dx;
					ny -= dy;
					board[nx][ny] = player;
				}
			}
		}
	}
};

/*
*@param (flag) count the number of pieces of each player
*/
void countPieces(int board[BOARD_SIZE][BOARD_SIZE], int *whiteCount, int *blackCount) {
	*whiteCount = 0;
	*blackCount = 0;
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (board[x][y] == 1) (*whiteCount)++;
			if (board[x][y] == 2) (*blackCount)++;
		}
	}
};


/*
*@param (flag) check if the game is over or not
*/
bool isGameOver(int board[BOARD_SIZE][BOARD_SIZE]) {
	int whiteCount, blackCount;
	countPieces(board, &whiteCount, &blackCount);

	if (whiteCount + blackCount == BOARD_SIZE * BOARD_SIZE) {
		return true;
	}

	bool whiteMovesAvailable = false;
	bool blackMovesAvailable = false;
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (board[x][y] == 0) {
				if (isValidMove(board, x, y, 1)) whiteMovesAvailable = true;
				if (isValidMove(board, x, y, 2)) blackMovesAvailable = true;
			}
		}
	}

	if (!whiteMovesAvailable && !blackMovesAvailable) {
		return true;
	}

	return false;
};

