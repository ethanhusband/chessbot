#ifndef LEGAL_H_SEEN
#define LEGAL_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include "../Pieces/Pawn/Pawn.h"
#include "../Pieces/Minor/Knight.h"
#include "../Pieces/Minor/Bishop.h"
#include "../Pieces/Major/Rook.h"
#include "../Pieces/Major/Queen.h"
#include "../Pieces/King/King.h"

int legal_input(board_t board, move_t *curmove);
int check_piece(board_t board, move_t *curmove);
int move_on_board(indexvector_t vector);
int capture_opposition(board_t board, move_t *curmove);


#endif /* !LEGAL_H_SEEN */