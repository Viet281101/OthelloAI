
/* pour Bocal */
#include <GL/gl.h> 
#include <GL/glut.h>
#include <GL/freeglut.h>  

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* pour Mac */
// #include <GLUT/glut.h>

#define BOARD_SIZE 8
#define CELL_SIZE 80
#define DEG2RAD (3.14159/180.0)

//// draw.c
void drawBoard();
void drawGridLines();
void drawStableCorners();
void drawPiece(int x, int y, int player);
void drawHintCircle(int x, int y, int player);

//// move.c
bool isValidMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
void makeMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
void countPieces(int board[BOARD_SIZE][BOARD_SIZE], int *whiteCount, int *blackCount);

