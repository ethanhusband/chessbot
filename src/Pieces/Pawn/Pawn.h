#ifndef PAWN_H_SEEN
#define PAWN_H_SEEN

#include "../../Utils/Types.h"
#include "../../Utils/Macros.h"
#include <stdlib.h>
#include <ctype.h>

int pawn_legal(board_t board, move_t *curmove);
void en_passent_available(board_t board, move_t *curmove, int *en_passent, int *en_passent_col);
int promotion(board_t board, move_t *curmove);
int en_passent_happened(board_t board, move_t *curmove);

#endif /* !PAWN_H_SEEN */