#ifndef LEGAL_H_SEEN
#define LEGAL_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include <limits.h>

int check_piece(board_t board, move_t *curmove);
int move_on_board(indexvector_t vector);
int capture_opposition(board_t board, move_t *curmove);

#endif /* !LEGAL_H_SEEN */