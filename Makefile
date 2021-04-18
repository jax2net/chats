CC=gcc
EXEC=main
LIBS=SDL2

make:
	$(CC) *.c -l$(LIBS) -o $(EXEC)
