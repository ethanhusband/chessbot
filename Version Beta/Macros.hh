// Macros (not Makris)

#define SENTINEL -1

#define BOARD_WIDTH 8
#define BOARD_SIZE BOARD_WIDTH*BOARD_WIDTH
#define TOTAL_PLAYERS 2
#define CASTLING_SIDES 2
#define TOTAL_CASTLES TOTAL_PLAYERS*CASTLING_SIDES

#define FEN_WHITE_NAME 'w'
#define FEN_BLACK_NAME 'b'


#define BITBOARDS_PER_STATE 12


/* ArrayBoard piece representations */
#define ARR_BLACK_PAWN 'p'
#define ARR_BLACK_KNIGHT 'n'
#define ARR_BLACK_BISHOP 'b'
#define ARR_BLACK_ROOK 'r'
#define ARR_BLACK_QUEEN 'q'
#define ARR_BLACK_KING 'k'
#define ARR_WHITE_PAWN 'P'
#define ARR_WHITE_KNIGHT 'N'
#define ARR_WHITE_BISHOP 'B'
#define ARR_WHITE_ROOK 'R'
#define ARR_WHITE_QUEEN 'Q'
#define ARR_WHITE_KING 'K'

#define CHECK_NUMBER_OF_BOARDS false