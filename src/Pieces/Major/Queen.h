#ifndef QUEEN_H_SEEN
#define QUEEN_H_SEEN

#include "../../Utils/Types.h"
#include "../../Utils/Macros.h"
#include "Rook.h"
#include "../Minor/Bishop.h"

int queen_legal(board_t board, move_t *curmove);

#endif /* !QUEEN_H_SEEN */