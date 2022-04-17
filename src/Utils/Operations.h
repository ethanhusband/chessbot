

/* MISCELLANEOUS OPERATIONS */

char itoc(int moveNode, int from);
int ctoi(char moveNode);
void make_indexvector(movechars_t cvector, indexvector_t ivector);
void make_movechars(movechars_t cvector, indexvector_t ivector);
void copy_board(board_t old_board, board_t new_board);
void update_board(board_t board, move_t *move);
void recursive_free(decision_node_t *root);