#include "Bishop.h"

int bishop_legal(board_t board, move_t *curmove) {
    /* Detect legality of a bishop move */
    int i, hozdist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL], \
        vertdist = curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW];
    if ((vertdist == 0) || (hozdist == 0) || (abs(hozdist) != abs(vertdist))) {
        return 0;
    }
    /* Find vertical direction */
    if (vertdist>0) {
        vertdist=1;
    } else {
        vertdist=-1;
    }
    /* Find horizontal direction */
    if (hozdist>0) {
        hozdist=1;
    } else {
        hozdist=-1;
    }
    /* Ensure no spaces in between target are occupied */
    for (i=1; i<abs(hozdist); i++) {
        if (board[curmove->vector[SOURCE_ROW]+i*vertdist][curmove->vector[SOURCE_COL]+i*hozdist] != '.') {
            return 0;
        }
    }
    return 1;
}