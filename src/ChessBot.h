/* GLOBAL MACROS (NOT MAKRIS) */

    /* The 'board reading' constants */
    #define BOARD_SIZE 8
    #define SENTINEL -1
    #define CELL_ORDINATES 2
    #define CHECK_MOVE 2
    #define BLACK_MOVE 0
    #define WHITE_MOVE 1

    /* INDEX MAPPINGS FOR A MOVE VECTOR */
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
    #define TOTAL_CASTLES 4

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

    /* DECISION TREE CONSTANTS */
    #define TREE_DEPTH 3
    #define INITIAL_DEPTH 0
    #define NO_OPTIONS 0
    #define INITIAL_SIZE 20


    /* STARTING BOARD */
    board_t starting_board = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, \
                            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, \
                            {'.', '.', '.', '.', '.', '.', '.', '.'},\
                            {'.', '.', '.', '.', '.', '.', '.', '.'},\
                            {'.', '.', '.', '.', '.', '.', '.', '.'},\
                            {'.', '.', '.', '.', '.', '.', '.', '.'},\
                            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},\
                            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
