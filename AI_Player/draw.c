
#include "game.h"

/*
*@param (flag) draw the Othello board with a single color (#009067)
*/
void drawBoard() {
	glColor3f(0.0, 0.56, 0.4); // Dark green using the hex color #009067
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			glRecti(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
		}
	}
};

/*
*@param (flag) draw grid lines on the board
*/
void drawGridLines() {
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
};

/*
*@param (flag) draw the stable corners (the four corners) of the board
*/
void drawStableCorners() {
	glColor3f(0.0, 0.0, 0.0);
	float radius = CELL_SIZE * 0.05;
	float offset = CELL_SIZE * 2.0;
	float corners[4][2] = {
		{offset, offset},
		{BOARD_SIZE * CELL_SIZE - offset, offset},
		{offset, BOARD_SIZE * CELL_SIZE - offset},
		{BOARD_SIZE * CELL_SIZE - offset, BOARD_SIZE * CELL_SIZE - offset}
	};

	for (int i = 0; i < 4; i++) {
		glBegin(GL_POLYGON);
		for (int j = 0; j < 360; j++) {
			float degInRad = j * DEG2RAD;
			glVertex2f(cos(degInRad) * radius + corners[i][0], sin(degInRad) * radius + corners[i][1]);
		}
		glEnd();
	}
};

/*
*@param (flag) draw a piece at (x, y) with the given player
*/
void drawPiece(int x, int y, int player) {
	glColor3f(player == 1 ? 1.0 : 0.0, player == 1 ? 1.0 : 0.0, player == 1 ? 1.0 : 0.0); // White for player 1, black for player 2
	float centerX = (x + 0.5) * CELL_SIZE;
	float centerY = (BOARD_SIZE - y - 0.5) * CELL_SIZE;
	float radius = CELL_SIZE * 0.4; // Adjust radius size as needed

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f(cos(degInRad) * radius + centerX, sin(degInRad) * radius + centerY);
	}
	glEnd();
};


/*
*@param (flag) draw a hint circle at (x, y) with the given player
*/
void drawHintCircle(int x, int y, int player) {
	if (player == 1) {
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

/*
*@param (flag) draw text on the screen
*/
void drawText(char *text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double *matrix = malloc(sizeof(double) * 16);
	void *font = GLUT_BITMAP_HELVETICA_18;
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(font, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
};


/*
*@param (flag) draw the Othello score board
*/
void drawScoreBoard(int whiteCount, int blackCount, int currentPlayer, int board[BOARD_SIZE][BOARD_SIZE]) {
	char *whiteScore = malloc(sizeof(char) * 10);
	char *blackScore = malloc(sizeof(char) * 10);
	char *currentPlayerText = malloc(sizeof(char) * 10);
	char *player1 = "You";
	char *player2 = "AI";

	sprintf(whiteScore, "%d", whiteCount);
	sprintf(blackScore, "%d", blackCount);
	if (isGameOver(board)) {
		if (whiteCount > blackCount) {
			sprintf(currentPlayerText, "GAME OVER ! %s wins!", player1);
		} else if (whiteCount < blackCount) {
			sprintf(currentPlayerText, "GAME OVER ! %s wins!", player2);
		} else {
			sprintf(currentPlayerText, "GAME OVER ! Draw!");
		}
	} else {
		if (currentPlayer == 1) {
			sprintf(currentPlayerText, "%sr's turn", player1);
		} else if (currentPlayer == 2) {
			sprintf(currentPlayerText, "%s's turn", player2);
		}
	}

	glColor3f(0.0, 40.0, 200.0); // Blue color for the score board text
	drawText("White", 5, 10, 580);
	drawText(whiteScore, strlen(whiteScore), 10, 560);
	drawText("Black", 5, 10, 520);
	drawText(blackScore, strlen(blackScore), 10, 500);
	drawText(currentPlayerText, strlen(currentPlayerText), 10, 460);
};

