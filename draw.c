
#include "game.h"

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
