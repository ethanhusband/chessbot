#ifndef KING_H_SEEN
#define KING_H_SEEN

#include "../../Utils/Types.h"
#include "../../Utils/Macros.h"
#include <stdlib.h>
/* Some functions related to castling are obviously required */
#include "../Major/Rook.h"

int king_legal(board_t board, move_t *curmove);

#endif /* !KING_H_SEEN */