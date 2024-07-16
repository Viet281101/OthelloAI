# AI for Othello Game

![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Viet281101/OthelloAI) ![Github language count](https://img.shields.io/github/languages/count/Viet281101/OthelloAI) ![GitHub Created At](https://img.shields.io/github/created-at/Viet281101/OthelloAI)

An Othello game with AI using C language and [OpenGL](https://github.com/McNopper/OpenGL) GLUT. There are 2 game modes: playing with a human and playing with artificial intelligence.

To learn how to play Othello, click on the following image:

[![alt text](othello_start.png)](https://www.eothello.com/)

## Compilation

### Prerequisites:
- Install Make with the command:
	```bash
	sudo apt-get install make
	```
- And install [GLUT](https://github.com/FreeGLUTProject/freeglut):
	```bash
	sudo apt-get install freeglut3 freeglut3-dev
	```
	or
	```bash
	sudo apt-get install libglut3-dev
	```

- Clone the project from [my GitHub](https://github.com/Viet281101/OthelloAI) to your computer:
	```bash
	git clone https://github.com/Viet281101/OthelloAI.git
	```


### To compile the game:
- Go to the project directory "AI_Player" or "Human_Player"
	```bash
	cd Human_Player/
	```
	or
	```bash
	cd AI_Player/
	```
- Compile with the Makefile:
	```bash
	make
	```

## Launch:
- Run the **othello** file
	```bash
	./othello
	```

## Clean:
- Clean the files with make:
	```bash
	make clean
	```