#include "Pawn.h"

int pawn_legal(board_t board, move_t *curmove) {
    /* Verify a pawn move is legal */
    /* Can assume it is on the board and source cells exist, assume not en_passent */
    int vertmovedist = abs(curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW]);
    int hozmovedist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]);
    char targetsquare = board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]];
    /* Ahead cell is empty */
    if (curmove->movenum%CHECK_MOVE==WHITE_MOVE) {
        /* Could be a two space move */
        if ((curmove->vector[SOURCE_ROW] == WHITE_PAWN_ROW) && (vertmovedist == PAWN_START_DIST) && \
                (targetsquare == '.') && (board[curmove->vector[TARGET_ROW]-1][curmove->vector[TARGET_COL]] == '.') && \
                (hozmovedist == 0)) {
            return 1;
        /* Could be a move one space ahead */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == 0) && (targetsquare == '.')) {
            return 1;
        /* Must be a capture, not en passent */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == PAWN_MOVE_DIST) && \
                    (islower(board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]]))) {
            return 1;
        } else {
            /* This must not be legal */
            return 0;
        }
    } else {
        /* Could be a two space move */
        if ((curmove->vector[SOURCE_ROW] == BLACK_PAWN_ROW) && (vertmovedist == PAWN_START_DIST) && \
                (targetsquare == '.') && (board[curmove->vector[TARGET_ROW]+1][curmove->vector[TARGET_COL]] == '.') && \
                (hozmovedist == 0)) {
            return 1;
        /* Could be a move one space ahead */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == 0) && (targetsquare == '.')) {
            return 1;
        /* Must be a capture, not en passent */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == PAWN_MOVE_DIST) && \
                    (isupper(board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]]))) {
            return 1;
        } else {
            /* This must not be legal */
            return 0;
        }
    }
}

void en_passent_available(board_t board, move_t *curmove, int *en_passent, int *en_passent_col) {
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    if ((sourcepiece == BLACK_PAWN) || (sourcepiece == WHITE_PAWN)) {
        if (abs(curmove->vector[SOURCE_ROW] - curmove->vector[TARGET_ROW]) == PAWN_START_DIST) {
            *en_passent = 1;
            *en_passent_col = curmove->vector[SOURCE_COL];
        }
    } else {
        *en_passent = 0;
        *en_passent_col = SENTINEL;
    }
}



int promotion(board_t board, move_t *curmove) {
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    if ((curmove->movenum%CHECK_MOVE == WHITE_MOVE) && (sourcepiece == WHITE_PAWN) && (curmove->vector[TARGET_ROW] == 7)) {
        return 1;
    } else if ((curmove->movenum%CHECK_MOVE == BLACK_MOVE) && (sourcepiece == WHITE_PAWN) && (curmove->vector[TARGET_ROW] == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int en_passent_happened(board_t board, move_t *curmove) {
    /* Assumes sourcepiece and board locations are correct */
    /* Return 1 if an en_passent capture happened, 0 otherwise */
    if (!curmove->en_passent) {
        return 0;
    }
    int move = curmove->movenum%CHECK_MOVE, vertdist=curmove->vector[TARGET_ROW]-curmove->vector[SOURCE_ROW],\
        hozdist=abs(curmove->vector[TARGET_COL]-curmove->vector[SOURCE_COL]);
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    /* Ensure move is even with the right piece */
    if ((sourcepiece != BLACK_PAWN) || (sourcepiece != WHITE_PAWN))  {
        return 0;
    /* Ensure capture is possible with piece, and move is diagonal */
    } else if ((curmove->vector[TARGET_COL] == curmove->en_passent_col) && (hozdist == 1)) {
        /* Ensure capture was with the right piece and of the opposition */
        if ((move==WHITE_MOVE) && (sourcepiece == WHITE_PAWN) && (curmove->vector[SOURCE_ROW] == EN_PASSENTWROW) && \
            (islower(board[curmove->vector[TARGET_ROW-1]][curmove->vector[TARGET_COL]])) && (vertdist == 1)) {
            return 1;
        } else if ((sourcepiece == BLACK_PAWN) && (curmove->vector[SOURCE_ROW] == EN_PASSENTWROW) && \
                    (isupper(board[curmove->vector[TARGET_ROW+1]][curmove->vector[TARGET_COL]])) && (vertdist == -1)) {
            return 1;
        }
    } 
    return 0;
}