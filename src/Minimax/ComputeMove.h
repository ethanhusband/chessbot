#ifndef COMPUTE_MOVES_H_SEEN
#define COMPUTE_MOVES_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include <stdlib.h>

int play_round(board_t board, int move, int en_passent, int en_passent_col, castling_t rook_info);
void recursive_addlayers(decision_node_t *node, int move, int tree_depth);
void find_move(decision_node_t *root, move_t *best_move);

#endif /* ! COMPUTE_MOVES_H_SEEN */