
#include "game.h"

int isValidMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
    //// Check if the cell is empty
    if (board[x][y] != 0) {
        return 0;
    }

    //// Check if the move is valid
    int valid = 0;

    //// Check the right
    for (int i = x + 1; i < BOARD_SIZE; i++) {
        if (board[i][y] == 0) {
            break;
        }

        if (board[i][y] == player) {
            valid = 1;
            break;
        }
    }

    //// Check the left
    for (int i = x - 1; i >= 0; i--) {
        if (board[i][y] == 0) {
            break;
        }

        if (board[i][y] == player) {
            valid = 1;
            break;
        }
    }

    //// Check the top
    for (int i = y + 1; i < BOARD_SIZE; i++) {
        if (board[x][i] == 0) {
            break;
        }

        if (board[x][i] == player) {
            valid = 1;
            break;
        }
    }

    //// Check the bottom
    for (int i = y - 1; i >= 0; i--) {
        if (board[x][i] == 0) {
            break;
        }

        if (board[x][i] == player) {
            valid = 1;
            break;
        }
    }

    //// Check the top right
    for (int i = x + 1, j = y + 1; i < BOARD_SIZE && j < BOARD_SIZE; i++, j++) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            valid = 1;
            break;
        }
    }

    //// Check the top left
    for (int i = x - 1, j = y + 1; i >= 0 && j < BOARD_SIZE; i--, j++) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            valid = 1;
            break;
        }
    }

    //// Check the bottom right
    for (int i = x + 1, j = y - 1; i < BOARD_SIZE && j >= 0; i++, j--) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            valid = 1;
            break;
        }
    }

    //// Check the bottom left
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            valid = 1;
            break;
        }
    }

    return valid;
};

void makeMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
    //// Check the right
    for (int i = x + 1; i < BOARD_SIZE; i++) {
        if (board[i][y] == 0) {
            break;
        }

        if (board[i][y] == player) {
            for (int j = x + 1; j < i; j++) {
                board[j][y] = player;
            }

            break;
        }
    }

    //// Check the left
    for (int i = x - 1; i >= 0; i--) {
        if (board[i][y] == 0) {
            break;
        }

        if (board[i][y] == player) {
            for (int j = x - 1; j > i; j--) {
                board[j][y] = player;
            }

            break;
        }
    }

    //// Check the top
    for (int i = y + 1; i < BOARD_SIZE; i++) {
        if (board[x][i] == 0) {
            break;
        }

        if (board[x][i] == player) {
            for (int j = y + 1; j < i; j++) {
                board[x][j] = player;
            }

            break;
        }
    }

    //// Check the bottom
    for (int i = y - 1; i >= 0; i--) {
        if (board[x][i] == 0) {
            break;
        }

        if (board[x][i] == player) {
            for (int j = y - 1; j > i; j--) {
                board[x][j] = player;
            }

            break;
        }
    }

    //// Check the top right
    for (int i = x + 1, j = y + 1; i < BOARD_SIZE && j < BOARD_SIZE; i++, j++) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            for (int k = x + 1, l = y + 1; k < i && l < j; k++, l++) {
                board[k][l] = player;
            }

            break;
        }
    }

    //// Check the top left
    for (int i = x - 1, j = y + 1; i >= 0 && j < BOARD_SIZE; i--, j++) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            for (int k = x - 1, l = y + 1; k > i && l < j; k--, l++) {
                board[k][l] = player;
            }

            break;
        }
    }

    //// Check the bottom right
    for (int i = x + 1, j = y - 1; i < BOARD_SIZE && j >= 0; i++, j--) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            for (int k = x + 1, l = y - 1; k < i && l > j; k++, l--) {
                board[k][l] = player;
            }

            break;
        }
    }

    //// Check the bottom left
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 0) {
            break;
        }

        if (board[i][j] == player) {
            for (int k = x - 1, l = y - 1; k > i && l > j; k--, l--) {
                board[k][l] = player;
            }

            break;
        }
    }

    //// Place the piece on the board
    board[x][y] = player;
};

