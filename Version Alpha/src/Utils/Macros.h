#ifndef MACROS_H_SEEN
#define MACROS_H_SEEN

/* GLOBAL MACROS (NOT MAKRIS) */

    /* CONTROLS - FOR MODIFYING WHAT THE PROGRAM ITSELF DOES */
    #define DEBUG 1
    #define RELAY_GAME 1
    #define COMPUTING_MOVE 0
    #define FEN_INPUT 0
    #define CHECK_LEGAL 0

    /* To comment out things with comments in them - exclude code */
    #define EXCLUDED 0

    /* DECISION TREE CONSTANTS */
    #define TREE_DEPTH 3
    #define INITIAL_DEPTH 0
    #define NO_OPTIONS 0
    #define INITIAL_SIZE 10

    /* Always necessary */
    #define TRUE 1
    #define FALSE 0

    /* The 'board reading' constants */
    #define BOARD_SIZE 8
    #define SENTINEL -1
    #define CELL_ORDINATES 2
    #define CHECK_MOVE 2
    #define BLACK_MOVE 0
    #define WHITE_MOVE 1

    /* INDEX MAPPINGS FOR A MOVE VECTOR */
    #define MOVE_VECTOR_SIZE 4
    #define SOURCE_ROW 0
    #define SOURCE_COL 1
    #define TARGET_ROW 2
    #define TARGET_COL 3

    /* MISC CONSTANTS */
    #define WHITE_PAWN_ROW 1
    #define BLACK_PAWN_ROW 6
    #define PAWN_START_DIST 2
    #define PAWN_MOVE_DIST 1
        /* Only rows from which en passent is possible, for each color  */
    #define EN_PASSENTWROW 4
    #define EN_PASSENTBROW 3

    /* CASTLE_INFO CONSTANTS */
    #define TOTAL_CASTLES 4
    #define A1ROOK_INDEX 0
    #define A8ROOK_INDEX 1
    #define H1ROOK_INDEX 2
    #define H8ROOK_INDEX 3

    /* EVAL BAR CONSTANTS */
    #define PAWN_COST 100
    #define KNIGHT_COST 300
    #define BISHOP_COST 300
    #define ROOK_COST 500
    #define QUEEN_COST 900
    #define KING_COST INT_MAX/2

    /* PIECE REPRESENTATION CONSTANTS */
    #define EMPTY_CELL '.'

    #define BLACK_PAWN 'p'
    #define BLACK_KNIGHT 'n'
    #define BLACK_BISHOP 'b'
    #define BLACK_ROOK 'r'
    #define BLACK_QUEEN 'q'
    #define BLACK_KING 'k'

    #define WHITE_PAWN 'P'
    #define WHITE_KNIGHT 'N'
    #define WHITE_BISHOP 'B'
    #define WHITE_ROOK 'R'
    #define WHITE_QUEEN 'Q'
    #define WHITE_KING 'K'

    /* CONSTANTS FOR BOARD PRINTING */
    #define ROW_SEPERATOR "   +---+---+---+---+---+---+---+---+\n"
    #define MOVE_SEPERATOR "=====================================\n"
    #define TEAM_PIECES 12
    #define COLUMNS "     A   B   C   D   E   F   G   H\n"
    #define PROGRAM_MOVE "*** "
        /* Boolean value for indicating whether the move being printed was made by the computer */
    #define IS_COMPUTER_MOVE 1

    

#endif /* !MACROS_H_SEEN */