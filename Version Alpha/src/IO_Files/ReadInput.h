#ifndef INPUT_H_SEEN
#define INPUT_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include "../Legal/Legal.h"
#include "../Utils/Operations.h"
#include "../Pieces/Major/Rook.h"
#include "PrintBoard.h"
#include <stdio.h>

int read_movesfile(board_t board, move_t *curmove);

#endif /* !INPUT_H_SEEN */