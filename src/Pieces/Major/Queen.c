#include "Queen.h"

int queen_legal(board_t board, move_t *curmove) {
    /* Detect legality of a queen move */
    int hozdist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL], \
        vertdist = curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW];
    /* Can simply be reduced to bishop or rook case */
    if ((hozdist == 0) || (vertdist == 0)) {
        printf("CHECKING ROOK\n");
        return rook_legal(board, curmove);
    } else {
        return bishop_legal(board, curmove);
    }
}