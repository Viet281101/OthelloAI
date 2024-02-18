
#include "game.h"
#include "minimax.h"
#include "alphabeta.h"

FILE *logFile;
int board[BOARD_SIZE][BOARD_SIZE];
int currentPlayer = 1; // 1 = white, 2 = black
int turnCount = 0;


void initBoard() {
	memset(board, 0, sizeof(board));
	int mid = BOARD_SIZE / 2;
	board[mid][mid] = 1;
	board[mid-1][mid-1] = 1;
	board[mid-1][mid] = 2;
	board[mid][mid-1] = 2;
}

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
	printf("White (AI 1): %d, Black (AI 2): %d\n", whiteCount, blackCount);
	fprintf(logFile, "White (AI 1): %d, Black (AI 2): %d\n", whiteCount, blackCount);
	if (isGameOver(board)) {
		if (whiteCount > blackCount) {
			printf("GAME OVER! AI 1 wins!\n");
			fprintf(logFile, "GAME OVER! AI 1 wins!\n");
		} else if (whiteCount < blackCount) {
			printf("GAME OVER! AI 2 wins!\n");
			fprintf(logFile, "GAME OVER! AI 2 wins!\n");
		} else {
			printf("GAME OVER! It's a draw!\n");
			fprintf(logFile, "GAME OVER! It's a draw!\n");
		}
		logBoardState(logFile, board);
	} else {
		printf("AI 1's turn\n\n");
		fprintf(logFile, "AI 1's turn\n\n");
	}
};

void displayGame() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawBoard();
	drawGridLines();
	drawStableCorners();

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (board[x][y] != 0) {
				drawPiece(x, y, board[x][y]);
			}
		}
	}

	int whiteCount, blackCount;
	countPieces(board, &whiteCount, &blackCount);
	drawScoreBoard(whiteCount, blackCount, turnCount, currentPlayer, board);
	glFlush();
};

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int bestMove[2] = {-1, -1};

		if (currentPlayer == 1) {
			findBestMoveMinimax(board, currentPlayer, 5, bestMove);
		} else {
			findBestMoveAlphaBeta(board, currentPlayer, 5, bestMove);
		}

		if (bestMove[0] != -1 && bestMove[1] != -1) {
			makeMove(board, bestMove[0], bestMove[1], currentPlayer);
			turnCount++;

			int whiteCount, blackCount;
			countPieces(board, &whiteCount, &blackCount);

			printf("Turn %d: AI %d made a move.\n", turnCount, (currentPlayer == 1) ? 2 : 1);
			fprintf(logFile, "Turn %d: AI %d made a move.\n", turnCount, (currentPlayer == 1) ? 2 : 1);
			checkTurnCountPieces(whiteCount, blackCount);
			logBoardState(logFile, board);
			fflush(logFile);

			currentPlayer = (currentPlayer == 1) ? 2 : 1;
		}

		glutPostRedisplay();
	}
};

void display() {
	displayGame();
};

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
};

int main(int argc, char **argv) {
	logFile = fopen("GameLog/game_log.txt", "w");
	if (logFile == NULL) {
		printf("Error opening file!\n");
		exit(EXIT_FAILURE);
	}

	initBoard();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Othello Game AI vs AI");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMainLoop();

	fclose(logFile);
	return 0;
};

