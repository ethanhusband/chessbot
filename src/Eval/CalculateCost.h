#ifndef COST_H_SEEN
#define COST_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include <limits.h>

int material_cost(board_t board);
int positional_cost(board_t board);
double aggregate_cost(board_t board);
int square_threat(board_t board, int row, int col, int player);

#endif /* !COST_H_SEEN */