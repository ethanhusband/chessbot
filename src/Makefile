CC=gcc

chessbot: ChessBot.c Operations.o
	$(CC) -Wall -ansi -o chessbot ChessBot.c

Operations.o: Operations.c Operations.h
	$(CC) -Wall -ansi -c Operations.c