
#include "game.h"

int board[BOARD_SIZE][BOARD_SIZE];
int currentPlayer = 1; //// 1 = white, 2 = black

/*
*@param (flag) initialize the board with the initial four pieces at the center of the board
*/
void initBoard() {
	//// Clear the board
	memset(board, 0, sizeof(board));

	//// Set up the initial four pieces
	int mid = BOARD_SIZE / 2;
	board[mid][mid] = 1;
	board[mid-1][mid-1] = 1;
	board[mid-1][mid] = 2;
	board[mid][mid-1] = 2;
};


void checkTurnCountPieces() {
	int whiteCount, blackCount;
	countPieces(board, &whiteCount, &blackCount);
	printf("White: %d, Black: %d\n", whiteCount, blackCount);
	if (currentPlayer == 1) {
		printf("White's turn\n");
	} else {
		printf("Black's turn\n");
	}
	if (whiteCount + blackCount == BOARD_SIZE * BOARD_SIZE) {
		if (whiteCount > blackCount) {
			printf("White wins!\n");
		} else if (whiteCount < blackCount) {
			printf("Black wins!\n");
		} else {
			printf("Draw!\n");
		}
	}
};

/*
*@param (flag) the current board state to be displayed
*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	//// Draw the Othello board
	drawBoard();

	//// Draw the grid lines
	drawGridLines();

	//// Draw the stable corners
	drawStableCorners();

	//// Draw the pieces
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (board[x][y] != 0) {
				drawPiece(x, y, board[x][y]);
			}
		}
	}

	//// Draw the hint circle
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (board[x][y] == 0 && isValidMove(board, x, y, currentPlayer)) {
				drawHintCircle(x, y, currentPlayer);
			}
		}
	}

	//// Check the turn and count the pieces
	checkTurnCountPieces();

	glFlush();
};

/*
*@param (flag) handle the mouse click event
*/
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//// Get the cell position
		int cellX = x / CELL_SIZE;
		int cellY = y / CELL_SIZE;

		//// Check if the cell is empty
		if (board[cellX][cellY] == 0) {
			//// Check if the move is valid
			if (isValidMove(board, cellX, cellY, currentPlayer)) {
				//// Place the piece on the board
				makeMove(board, cellX, cellY, currentPlayer);

				//// Change the player
				currentPlayer = (currentPlayer == 1) ? 2 : 1;
			}
		}

		//// Redraw the scene
		glutPostRedisplay();
	}
};


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, BOARD_SIZE * CELL_SIZE, 0.0, BOARD_SIZE * CELL_SIZE);
	initBoard();
};


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Othello Game");
	init();
	glutMouseFunc(mouseClick);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
};
