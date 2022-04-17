
void update_rooks(board_t board, move_t *curmove, castling_t rook_info);
int rook_legal(board_t board, move_t *curmove);
int castling_happened(board_t board, move_t *curmove);
int castling_legal(board_t board, move_t *curmove);