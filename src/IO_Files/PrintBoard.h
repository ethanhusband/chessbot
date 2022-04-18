#ifndef PRINT_H_SEEN
#define PRINT_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include "../Utils/Operations.h"
#include <stdio.h>
#include "../Eval/CalculateCost.h"

void print_move(board_t board, int programmove, move_t *curmove);
void print_board(board_t board);

#endif /* !PRINT_H_SEEN */