
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
*@param (flag) draw the Othello score board
*/
void drawScoreBoard(int whiteCount, int blackCount, int currentPlayer) {};

