CC=gcc
EXEC=main
LIBS=-lSDL2 -lSDL2_ttf

make:
	$(CC) *.c $(LIBS) -o $(EXEC)
