#include "ChessBot.h"
#include "Types.h"


/**
 * @brief Prints out the board and other relevant information for a given move.
 *        This includes :
 *          - Indicating whether computer played the move
 *          - Showing which player played the move
 *          - What piece moved where
 *          - Material cost and eval of the current position UNFINISHED
 * 
 * @param board - 2D array representing a chess board
 * @param isComputerMove - Boolean indicating if move was made by computer
 * @param curmove - move_t object which provides information about what move just occurred
 */
void print_move(board_t board, int isComputerMove, move_t *curmove) {
    /* Convert index vector to the lettered coordinates */
    movechars_t output;
    make_movechars(output, curmove->vector);

    /* Prerequisite for all prints */
    printf(MOVE_SEPERATOR);

    /* Check if we're reading a move from an FEN or the program is playing it */
    if (isComputerMove) {
        printf(PROGRAM_MOVE);
    }

    /* Print if black or white is moving */
    if (curmove->movenum%CHECK_MOVE==WHITE_MOVE) {
        printf("WHITE ACTION #%d: ", curmove->movenum);
    } else {
        printf("BLACK ACTION #%d: ", curmove->movenum);
    }

    /* Print what piece moved in this move */
    printf("%c moves %c%c-%c%c\n", board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]], \
                output[SOURCE_COL], output[SOURCE_ROW], \
                output[TARGET_COL], output[TARGET_ROW]);
            
    /* Print cost/eval info */
    printf("MATERIAL COST: %d\n", material_cost(board)/100);
    /* UNFINISHED */
    printf("POSITIONAL COST: %d\n", positional_cost(board)/100);
    printf("AGGREGATE SCALED COST: %.1lf\n", aggregate_cost(board));
    /* UNFINISHED ^ */
    print_board(board);
}

/**
 * @brief Prints a provided board type
 * 
 * @param board - 2D array representing a chess board
 */
void print_board(board_t board) {

    /* Iterate through the 2D board array, printing each char */
    for (int i=BOARD_SIZE-1; i>=0; i--) {
        printf(ROW_SEPERATOR);
        /* Print the current row number on the side, with column seperator */
        printf(" %d |", i+1);
        /* Print every item in that row, with column seperator */
        for (int j=0; j<BOARD_SIZE; j++) {
            printf(" %c |", board[i][j]);
        }
        putchar('\n');
    }
    printf(ROW_SEPERATOR);
    printf(COLUMNS);
}