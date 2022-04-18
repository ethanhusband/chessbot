#ifndef OPERATIONS_H_SEEN
#define OPERATIONS_H_SEEN

#include "../Utils/Types.h"
#include "../Utils/Macros.h"
#include "../Pieces/Pawn/Pawn.h"
#include "../Pieces/Major/Rook.h"
#include <stdlib.h>
#include <assert.h>

/* MISCELLANEOUS DATA OPERATIONS */

char itoc(int moveNode, int from);
int ctoi(char moveNode);
void make_indexvector(movechars_t cvector, indexvector_t ivector);
void make_movechars(movechars_t cvector, indexvector_t ivector);
void expand_array(decision_node_t *possible_moves, int index, int *cursize);
void copy_board(board_t old_board, board_t new_board);
void update_board(board_t board, move_t *move);
void recursive_free(decision_node_t *root);

#endif /* !OPERATIONS_H_SEEN */