#include "ReadInput.h"

/**
 * @brief - Reads the moves from a given movesfile onto main board and main curmove. Returns TRUE or FALSE if legal.
 * 
 * @param board - 2D array representing the board
 * @param curmove - Represents a move made within a game
 * @return Boolean - Returns TRUE if input was all legal
 */
Boolean read_movesfile(board_t board, move_t *curmove) {
    /* Interpret the input from a movesFile, update the board.
    Return 1 if input is valid, 0 otherwise */
    int can_en_passent=0, en_passent_col=SENTINEL, i;
    char sourcepiece;
    movechars_t cvector;
    indexvector_t ivector;
    while (scanf("%c%c-%c%c\n", &cvector[SOURCE_COL], &cvector[SOURCE_ROW], &cvector[TARGET_COL], &cvector[TARGET_ROW]) != EOF) { 
        (curmove->movenum)++;

    #if DEBUG
        printf("MOVE READ: %c%c-%c%c\n", cvector[SOURCE_COL], cvector[SOURCE_ROW], cvector[TARGET_COL], cvector[TARGET_ROW]);
    #endif
        /* Translate read char vector to index vector */
        make_indexvector(cvector, ivector);
    #if DEBUG
        printf("MOVE CONVERTED: %d,%d-%d,%d\n", ivector[SOURCE_ROW], ivector[SOURCE_COL], ivector[TARGET_ROW], ivector[TARGET_COL]);
    #endif

        /* Assign read index vector to the curmove structure */
        for (i=0; i<CELL_ORDINATES*CELL_ORDINATES; i++) {
            curmove->vector[i] = ivector[i];
        }

#if CHECK_LEGAL
    /* Ensure the input is legal */
    if (!legal_input(board, curmove)) {
        printf("TERMINATED: ILLEGAL INPUT\n");
        return FALSE;
    }
#endif

        /* Update which rooks can still castle */
        update_castling_info(board, curmove);
        update_board(board, curmove);
#if RELAY_GAME
        print_move(board, !IS_COMPUTER_MOVE, curmove);
#endif
    }
    return TRUE;
}