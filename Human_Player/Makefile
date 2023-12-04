
SHELL = /bin/sh
#definition des commandes utilisees
CC = gcc
MACHINE= $(shell uname -s)
#declaration des options du compilateur
#PG_FLAGS = -DOPENGL_1_5

ifeq ($(MACHINE), Darwin)
GL_LDFLAGS = -framework OpenGL -framework GLUT -framework Cocoa
else
GL_LDFLAGS = -lGL -lglut -lGLU
endif

CFLAGS = -Wall -Wno-sequence-point
LDFLAGS = -lm $(GL_LDFLAGS)
#definition des fichiers et dossiers
PROGNAME = othello
HEADERS = game.h
SOURCES = main.c move.c draw.c
OBJ = $(SOURCES:.c=.o)
DELPROG = compressed_image.rle

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	@$(RM) $(PROGNAME) $(OBJ) *~ gmon.out core.*
	@$(RM) $(DELPROG)
