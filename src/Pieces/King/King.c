#include "King.h"

int king_legal(board_t board, move_t *curmove) {
    int hozdist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]), \
        vertdist = abs(curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW]);
    if (castling_happened(board, curmove)) {
        return castling_legal(board, curmove);
    } else if (!(hozdist==1 || vertdist==1)) {
        return 0;
    }
    return 1;
}