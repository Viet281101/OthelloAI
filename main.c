
#include "game.h"

int board[BOARD_SIZE][BOARD_SIZE];
int currentPlayer = 1; //// 1 = white, 2 = black


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
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the Othello board with a single color (#009067)
    glColor3f(0.0, 0.56, 0.4); // Dark green using the hex color #009067
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            glRecti(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
        }
    }

    // Draw the grid lines
    glColor3f(0.0, 0.0, 0.0); // Black color for the lines
    glBegin(GL_LINES);
    for (int i = 0; i <= BOARD_SIZE; i++) {
        // Vertical lines
        glVertex2f(i * CELL_SIZE, 0);
        glVertex2f(i * CELL_SIZE, BOARD_SIZE * CELL_SIZE);
        // Horizontal lines
        glVertex2f(0, i * CELL_SIZE);
        glVertex2f(BOARD_SIZE * CELL_SIZE, i * CELL_SIZE);
    }
    glEnd();

	// Draw the stable corners
	drawStableCorners();

    glFlush();
};


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
