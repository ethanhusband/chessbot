CC=gcc

# Dependencies split according to their directories. Multiline dependency statement unavailable
chessbot: ChessBot.o Operations.o Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o CalculateCost.o PrintBoard.o ReadInput.o ComputeMove.o FindMinCost.o GetOptionsTree.o Legal.o
	$(CC) -Wall -o chessbot ChessBot.o Operations.o Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o CalculateCost.o PrintBoard.o ReadInput.o ComputeMove.o FindMinCost.o GetOptionsTree.o Legal.o

ChessBot.o: ../Chessbot.c
	$(CC) -Wall -c ../ChessBot.c

# UTILS 

Operations.o: ../Utils/Operations.c ../Utils/Operations.h
	$(CC) -Wall -c ../Utils/Operations.c

# PIECES

Pawn.o: ../Pieces/Pawn/Pawn.c ../Pieces/Pawn/Pawn.h
	$(CC) -Wall -c ../Pieces/Pawn/Pawn.c

Knight.o: ../Pieces/Minor/Knight.c ../Pieces/Minor/Knight.h
	$(CC) -Wall -c ../Pieces/Minor/Knight.c

Bishop.o: ../Pieces/Minor/Bishop.c ../Pieces/Minor/Bishop.h
	$(CC) -Wall -c ../Pieces/Minor/Bishop.c

Rook.o: ../Pieces/Major/Rook.c ../Pieces/Major/Rook.h
	$(CC) -Wall -c ../Pieces/Major/Rook.c

Queen.o: ../Pieces/Major/Queen.c ../Pieces/Major/Queen.h
	$(CC) -Wall -c ../Pieces/Major/Queen.c

King.o: ../Pieces/King/King.c ../Pieces/King/King.h
	$(CC) -Wall -c ../Pieces/King/King.c

# EVAL

CalculateCost.o: ../Eval/CalculateCost.c ../Eval/CalculateCost.h
	$(CC) -Wall -c ../Eval/CalculateCost.c

# IO FILES

PrintBoard.o: ../IO_Files/PrintBoard.c ../IO_Files/PrintBoard.h
	$(CC) -Wall -c ../IO_Files/PrintBoard.c

ReadInput.o: ../IO_Files/ReadInput.c ../IO_Files/ReadInput.h
	$(CC) -Wall -c ../IO_Files/ReadInput.c

# MINIMAX

ComputeMove.o: ../Minimax/ComputeMove.c ../Minimax/ComputeMove.h
	$(CC) -Wall -c ../Minimax/ComputeMove.c

FindMinCost.o: ../Minimax/FindMinCost.c ../Minimax/FindMinCost.h
	$(CC) -Wall -c ../Minimax/FindMinCost.c

GetOptionsTree.o: ../Minimax/GetOptionsTree.c ../Minimax/GetOptionsTree.h
	$(CC) -Wall -c ../Minimax/GetOptionsTree.c

# LEGAL

Legal.o: ../Legal/Legal.c ../Legal/Legal.h
	$(CC) -Wall -c ../Legal/Legal.c