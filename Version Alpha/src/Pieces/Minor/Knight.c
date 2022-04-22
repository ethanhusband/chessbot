#include "Knight.h"

int knight_legal(board_t board, move_t *curmove) {
    /* Detect legality of knight move */
    int hozdist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]), \
        vertdist = abs(curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW]);
    /* Cause it can jump this is easy to check, just ensure it moves the right distance */
    if (!(((vertdist == 2) && (hozdist == 1)) || ((vertdist == 1) && (hozdist == 2)))) {
        return 0;
    } else {
        return 1;
    }
}