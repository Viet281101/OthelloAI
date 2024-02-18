
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* pour Bocal */
#include <GL/gl.h> 
#include <GL/glut.h>
#include <GL/freeglut.h>  

/* pour Mac */
// #include <GLUT/glut.h>

#define BOARD_SIZE 8
#define CELL_SIZE 80
#define DEG2RAD (3.14159/180.0)

#define WINDOW_WIDTH (BOARD_SIZE * CELL_SIZE)
#define WINDOW_HEIGHT (BOARD_SIZE * CELL_SIZE)
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_X (WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2)
#define MINIMAX_BUTTON_Y 200
#define ALPHABETA_BUTTON_Y (MINIMAX_BUTTON_Y + BUTTON_HEIGHT + 50) 

#ifndef GAME_H
#define GAME_H

////////////////////////
////* -- draw.c -- *////

void drawBoard();
void drawGridLines();
void drawStableCorners();
void drawPiece(int x, int y, int player);
void drawHintCircle(int x, int y, int player);
void drawScoreBoard(int whiteCount, int blackCount, int turnCount, int currentPlayer, int board[BOARD_SIZE][BOARD_SIZE]);
void drawButton(char *text, int x, int y);


////////////////////////
////* -- move.c -- *////

bool isValidMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
void makeMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
void countPieces(int board[BOARD_SIZE][BOARD_SIZE], int *whiteCount, int *blackCount);
bool isGameOver(int board[BOARD_SIZE][BOARD_SIZE]);


////////////////////////
////* -- ai.c -- *////

int copyBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]);
int evaluateBoard(int board[BOARD_SIZE][BOARD_SIZE], int player);
void testAI();

#endif
