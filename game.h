
/* pour Bocal */
#include <GL/gl.h> 
#include <GL/glut.h>
#include <GL/freeglut.h>  

#include <math.h>

/* pour Mac */
// #include <GLUT/glut.h>

#define BOARD_SIZE 8
#define CELL_SIZE 80
#define DEG2RAD (3.14159/180.0)

int isValidMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
void makeMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
