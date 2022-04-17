#include "Types.h"
#include "Macros.h"
#include "ReadInput.h"
#include "Legal.h"
#include "Operations.h"
#include "PrintBoard.h"

int read_input(board_t board, int *moves, int *Men_passent, int *Men_passent_col, castling_t Mcastle_info) {
    /* Interpret the input, update the board.
    Return 1 if input is valid, 0 otherwise */
    int en_passent=0, en_passent_col=SENTINEL, i;
    char sourcepiece;
    movechars_t cvector;
    indexvector_t ivector;
    move_t *curmove;
    while (scanf("%c%c-%c%c\n", &cvector[SOURCE_COL], &cvector[SOURCE_ROW], \
            &cvector[TARGET_COL], &cvector[TARGET_ROW]) != EOF) { 
        (*moves)++;

        printf("MOVE READ: %c%c-%c%c\n", cvector[SOURCE_COL], cvector[SOURCE_ROW], cvector[TARGET_COL], cvector[TARGET_ROW]);
        make_indexvector(cvector, ivector);
        printf("MOVE CONVERTED: %d,%d-%d,%d\n", ivector[SOURCE_ROW], ivector[SOURCE_COL], ivector[TARGET_ROW], ivector[TARGET_COL]);

        curmove=(move_t*)malloc(sizeof(move_t));
        for (i=0; i<CELL_ORDINATES*CELL_ORDINATES; i++) {
            curmove->vector[i] = ivector[i];
        }
        curmove->movenum = *moves;
        curmove->en_passent = en_passent; 
        curmove->en_passent_col = en_passent_col;
        for (i=0; i<TOTAL_CASTLES; i++) {
            curmove->castle_info[i] = Mcastle_info[i];
        }
        /* Ensure the input is legal */
        if (!legal_input(board, curmove)) {
            printf("TERMINATED: ILLEGAL INPUT\n");
            return 0;
        }
        /* Update which rooks can still castle */
        sourcepiece = board[ivector[SOURCE_ROW]][ivector[SOURCE_COL]];
        if ((sourcepiece == WHITE_ROOK) || (sourcepiece == BLACK_ROOK)) {
            update_rooks(board, curmove, Mcastle_info);
        }
        /* En Passent is read to local variables after computing legality.
        This computation is then used to assign the en_passent values next round */
        en_passent_available(board, curmove, &en_passent, &en_passent_col);
        update_board(board, curmove);
        print_move(board, !IS_COMPUTER_MOVE, curmove);
        free(curmove);
    }
    *Men_passent = en_passent;
    *Men_passent_col = en_passent_col;
    return 1;
}