int pawn_legal(board_t board, move_t *curmove);
void en_passent_available(board_t board, move_t *curmove, int *en_passent, int *en_passent_col);
int promotion(board_t board, move_t *curmove);
int en_passent_happened(board_t board, move_t *curmove);