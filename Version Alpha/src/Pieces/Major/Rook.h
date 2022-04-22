#ifndef ROOK_H_SEEN
#define ROOK_H_SEEN

#include "../../Utils/Types.h"
#include "../../Utils/Macros.h"
#include "../../Eval/CalculateCost.h"
#include <stdlib.h>

void update_castling_info(board_t board, move_t *curmove);
int rook_legal(board_t board, move_t *curmove);
Boolean castling_happened(board_t board, move_t *curmove);
int castling_legal(board_t board, move_t *curmove);

#endif /* !ROOK_H_SEEN */