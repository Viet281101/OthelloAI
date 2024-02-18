
#include "game.h"
#include "minimax.h"
#include "alphabeta.h"

FILE *logFile;
bool inMenu = true;
bool withAlphaBeta = false;

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
*@param (flag) draw the board inside game log
*/
void logBoardState(FILE *logFile, int board[BOARD_SIZE][BOARD_SIZE]) {
	fprintf(logFile, "    A   B   C   D   E   F   G   H \n");
	fprintf(logFile, "  +---+---+---+---+---+---+---+---+\n");
	for (int y = 0; y < BOARD_SIZE; y++) {
		fprintf(logFile, "%d ", y + 1);
		for (int x = 0; x < BOARD_SIZE; x++) {
			char piece = ' ';
			if (board[x][y] == 1) piece = 'W'; // white
			else if (board[x][y] == 2) piece = 'B'; // black
			fprintf(logFile, "| %c ", piece);
		}
		fprintf(logFile, "| %d\n", y + 1);
		fprintf(logFile, "  +---+---+---+---+---+---+---+---+\n");
	}
	fprintf(logFile, "    A   B   C   D   E   F   G   H \n\n");
};

/*
*@param (flag) print stats of the game
*/
void checkTurnCountPieces(int whiteCount, int blackCount) {
	printf("White: %d, Black: %d\n", whiteCount, blackCount);
	fprintf(logFile, "White: %d, Black: %d\n", whiteCount, blackCount);
	if (isGameOver(board)) {
		if (whiteCount > blackCount) {
			printf("GAME OVER ! You wins!\n");
			fprintf(logFile, "GAME OVER ! You wins!\n");
		} else if (whiteCount < blackCount) {
			printf("GAME OVER ! AI wins!\n");
			fprintf(logFile, "GAME OVER ! AI wins!\n");
		} else {
			printf("GAME OVER ! Draw!\n");
			fprintf(logFile, "GAME OVER ! Draw!\n");
		}
		logBoardState(logFile, board);
	} else {
		if (currentPlayer == 1) {
			printf("Your's turn\n\n");
			fprintf(logFile, "Your's turn\n\n");
		} else if (currentPlayer == 2) {
			printf("AI's turn\n\n");
			fprintf(logFile, "AI's turn\n\n");
		}
	}
};

/*
* @param (flag) display the menu with 2 options: 1. Play with AI Minimax, 2. Play with AI Minimax with alpha-beta pruning
*/
void displayMenu() {
	glClear(GL_COLOR_BUFFER_BIT);

	//// Draw the menu title
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(100, 500);
	for (const char* c = "Play Othello Game with AI Minimax"; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	//// Draw the first button
	drawButton("With Alpha-Beta", BUTTON_X, MINIMAX_BUTTON_Y + 100);

	//// Draw the second button
	drawButton("Without Alpha-Beta", BUTTON_X, ALPHABETA_BUTTON_Y + 100);
};

/*
*@param (flag) the current board state to be displayed
*/
void displayGame() {
	if (!inMenu) {
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

		//// Draw the score board
		int whiteCount, blackCount;
		countPieces(board, &whiteCount, &blackCount);
		drawScoreBoard(whiteCount, blackCount, currentPlayer, board);
		checkTurnCountPieces(whiteCount, blackCount);
	}
};

/*
*@param (flag) handle the mouse click event in the menu
*/
void mouseClickMenu(int button, int state, int x, int y) {
	//// Check if the mouse click is inside the first button
	if (x >= BUTTON_X && x <= BUTTON_X + BUTTON_WIDTH && y >= MINIMAX_BUTTON_Y && y <= MINIMAX_BUTTON_Y + BUTTON_HEIGHT) {
		inMenu = false;
		withAlphaBeta = false;
		printf("You choose to play with AI Minimax\n\n");
		fprintf(logFile, "You choose to play with AI Minimax\n\n");
		initBoard();
		glutPostRedisplay();
	}

	//// Check if the mouse click is inside the second button
	if (x >= BUTTON_X && x <= BUTTON_X + BUTTON_WIDTH && y >= ALPHABETA_BUTTON_Y && y <= ALPHABETA_BUTTON_Y + BUTTON_HEIGHT) {
		inMenu = false;
		withAlphaBeta = true;
		printf("You choose to play with AI Minimax with Alpha-Beta Pruning\n\n");
		fprintf(logFile, "You choose to play with AI Minimax with Alpha-Beta Pruning\n\n");
		initBoard();
		glutPostRedisplay();
	}
};

/*
*@param (flag) handle the mouse click event in the board of game
*/
void mouseClickGame(int button, int state, int x, int y) {
	//// Get the cell position
	int cellX = x / CELL_SIZE;
	int cellY = y / CELL_SIZE;

	//// Check if the cell is empty
	if (board[cellX][cellY] == 0) {
		//// Check if the move is valid
		if (isValidMove(board, cellX, cellY, currentPlayer)) {
			//// Place the piece on the board
			if (board[cellX][cellY] == 0) makeMove(board, cellX, cellY, currentPlayer);

			if (isGameOver(board)) {
				printf("!!!! GAME OVER !!!!!!\n");
			} else {
				currentPlayer = 2; //// Switch to AI player

				//// Get the best move for the AI player
				int bestMove[2];
				int depth = 5;
				
				clock_t start, end;
				double cpu_time_used;
				start = clock();

				if (withAlphaBeta) {
					findBestMoveAlphaBeta(board, currentPlayer, depth, bestMove);
					
					end = clock();
					cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
					printf("Minimax with Alpha-Beta Pruning took %f seconds to execute \n", cpu_time_used);
					fprintf(logFile, "Minimax with Alpha-Beta Pruning took %f seconds to execute \n", cpu_time_used);
				} else {
					findBestMoveMinimax(board, currentPlayer, depth, bestMove);
					
					end = clock();
					cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
					printf("Minimax took %f seconds to execute \n", cpu_time_used);
					fprintf(logFile, "Minimax took %f seconds to execute \n", cpu_time_used);
				}

				//// Place the piece on the board
				if (board[bestMove[0]][bestMove[1]] == 0) {
					makeMove(board, bestMove[0], bestMove[1], currentPlayer);
				}

				if (isGameOver(board)) {
					printf("!!!! GAME OVER !!!!!!\n");
				} else {
					currentPlayer = 1; //// Switch to human player
				}

				logBoardState(logFile, board);

				glutPostRedisplay();
			}
		}
	}

	//// Redraw the scene
	glutPostRedisplay();
};

/*
*@param (flag) display the menu or the game
*/
void display() {
	if (inMenu) {
		displayMenu();
	} else {
		displayGame();
	}
	glFlush();
};

/*
*@param (flag) handle the mouse click event
*/
void mouseClick(int button, int state, int x, int y) {
	//// Check if the mouse click is inside the menu
	if (inMenu && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseClickMenu(button, state, x, y);
	} else if (!inMenu && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseClickGame(button, state, x, y);
	}
};

/*
*@param (flag) initialize the game
*/
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, BOARD_SIZE * CELL_SIZE, 0.0, BOARD_SIZE * CELL_SIZE);
};


int main(int argc, char** argv) {
	// testAI();
	logFile = fopen("GameLog/game_log.txt", "w");
	if (logFile == NULL) {
		printf("Error opening file!\n");
		perror("Error opening file!\n");
		exit(EXIT_FAILURE);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Othello Game (AI Player)");
	init();
	glutMouseFunc(mouseClick);
	glutDisplayFunc(display);
	glutMainLoop();
	fclose(logFile);
	return 0;
};
