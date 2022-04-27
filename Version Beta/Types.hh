#include "Macros.hh"
#include <string>

typedef uint64_t Bitboard;
/* Array board used as a data translation layer when reading input */
typedef char ArrayBoard[BOARD_WIDTH][BOARD_WIDTH];

/* An array of bitboards that stores the state of each type of piece in a game */
typedef Bitboard BoardState[BITBOARDS_PER_STATE];

/* Mapping of bitboard types to their index in a boardstate type */
enum BS_INDEX {
    BLACK_PAWN,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING,

    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING,
};

class MinimaxTree {
    public:
    #if CHECK_NUMBER_OF_BOARDS
        static long long int numberOfTrees;
    #endif
        BoardState currentBoard;


    
};