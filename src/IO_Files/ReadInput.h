#ifndef INPUT_H_SEEN
#define INPUT_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include "../Legal/Legal.h"
#include "../Utils/Operations.h"
#include "PrintBoard.h"
#include <stdio.h>

int read_movesfile(board_t board, int *moves, int *Men_passent, int *Men_passent_col, castling_t Mcastle_info);

#endif /* !INPUT_H_SEEN */