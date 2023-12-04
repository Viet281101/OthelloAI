
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

/*
*@param (flag) draw a hint circle at (x, y) with the given player
*/
void drawHintCircle(int x, int y) {
	if (currentPlayer == 1) {
		glColor3f(1.0, 1.0, 1.0); // White color hint
	} else {
		glColor3f(0.0, 0.0, 0.0); // Black color hint
	}
	float centerX = (x + 0.5) * CELL_SIZE;
	float centerY = (BOARD_SIZE - y - 0.5) * CELL_SIZE;
	float radius = CELL_SIZE * 0.4; // Adjust radius size as needed

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f(cos(degInRad) * radius + centerX, sin(degInRad) * radius + centerY);
	}
	glEnd();
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

	//// Draw the Othello board with a single color (#009067)
	glColor3f(0.0, 0.56, 0.4); // Dark green using the hex color #009067
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			glRecti(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
		}
	}

	//// Draw the grid lines
	glColor3f(0.0, 0.0, 0.0); // Black color for the lines
	glBegin(GL_LINES);
	for (int i = 0; i <= BOARD_SIZE; i++) {
		//// Vertical lines
		glVertex2f(i * CELL_SIZE, 0);
		glVertex2f(i * CELL_SIZE, BOARD_SIZE * CELL_SIZE);
		//// Horizontal lines
		glVertex2f(0, i * CELL_SIZE);
		glVertex2f(BOARD_SIZE * CELL_SIZE, i * CELL_SIZE);
	}
	glEnd();

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
				drawHintCircle(x, y);
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
