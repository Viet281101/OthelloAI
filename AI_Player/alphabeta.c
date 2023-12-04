
#include "alphabeta.h"



int copyBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        memcpy(newBoard[x], board[x], BOARD_SIZE * sizeof(int));
    }
};



int alphabeta(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard(board, player);
    }

    int opponent = (player == 1) ? 2 : 1;
    int bestScore = (player == 1) ? -1000000 : 1000000;

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (isValidMove(board, x, y, player)) {
                int newBoard[BOARD_SIZE][BOARD_SIZE];
                copyBoard(board, newBoard);
                makeMove(newBoard, x, y, player);

                int score = alphabeta(newBoard, opponent, depth - 1, alpha, beta);

                if (player == 1) {
                    if (score > bestScore) {
                        bestScore = score;
                    }
                    if (score > alpha) {
                        alpha = score;
                    }
                } else {
                    if (score < bestScore) {
                        bestScore = score;
                    }
                    if (score < beta) {
                        beta = score;
                    }
                }

                if (alpha >= beta) {
                    return bestScore;
                }
            }
        }
    }

    return bestScore;
};
