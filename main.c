
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
}

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
