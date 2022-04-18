#include "Rook.h"

int rook_legal(board_t board, move_t *curmove) {
    /* Detect legality of a rook move, assume not castling */
    int vertmovedist = curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW];
    int hozmovedist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL];
    int i;
    if ((vertmovedist == 0) && (hozmovedist >= 1)) {
        /* Horizontal positive path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_COL]+1; i<curmove->vector[TARGET_COL]; i++) {
            if (board[curmove->vector[SOURCE_ROW]][i] != '.') {
                return 0;
            }
        }
    } else if ((vertmovedist == 0) && (hozmovedist <= -1)) {
        /* Horizontal negative path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_COL]-1; i<curmove->vector[TARGET_COL]; i--) {
            if (board[curmove->vector[SOURCE_ROW]][i] != '.') {
                return 0;
            }
        }
    } else if ((vertmovedist == 0) && (hozmovedist >= 1)) {
        /* Vertical positive path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_ROW]+1; i<curmove->vector[TARGET_ROW]; i++) {
            if (board[i][curmove->vector[SOURCE_COL]] != '.') {
                return 0;
            }
        }
    } else if ((hozmovedist == 0) && (vertmovedist <= -1)) {
        /* Vertical negative path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_ROW]-1; i<curmove->vector[TARGET_ROW]; i--) {
            if (board[i][curmove->vector[SOURCE_COL]] != '.') {
                return 0;
            }
        }
    }
    return 1;
}

void update_rooks(board_t board, move_t *curmove, castling_t rook_info) {
    if ((curmove->vector[SOURCE_ROW] == 0) && (curmove->vector[SOURCE_COL] == 0)) {
        rook_info[0] = 0; 
    } else if ((curmove->vector[SOURCE_ROW] == 0) && (curmove->vector[SOURCE_COL] == 7)) {
        rook_info[1] = 0;
    } else if ((curmove->vector[SOURCE_ROW] == 7) && (curmove->vector[SOURCE_COL] == 0)) {
        rook_info[2] = 0;
    } else if ((curmove->vector[SOURCE_ROW] == 7) && (curmove->vector[SOURCE_COL] == 7)) {
        rook_info[3] = 0;
    }
}

int castling_happened(board_t board, move_t *curmove) {
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    int hozdist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]);
    if ((sourcepiece == 'K') && (hozdist == 2)) {
        return 1;
    } else {
        return 0;
    }
}

int castling_legal(board_t board, move_t *curmove) {
    /* Castling is represented uniquely as a king move of length 2, 
    which we can assume is already true */
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    int hozdist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL], i;
    if ((sourcepiece == 'K') && (hozdist<-1)) {
        if (!curmove->castle_info[0]) {
            return 0;
        }
        for (i=0; i<5; i++) {
            if (square_threat(board, 0, i, BLACK_MOVE)) {
                return 0;
            }
        }
    } else if ((sourcepiece == 'K') && (hozdist>1)) {
        if (!curmove->castle_info[1]) {
            return 0;
        }
        for (i=4; i<BOARD_SIZE; i++) {
            if (square_threat(board, 0, i, BLACK_MOVE)) {
                return 0;
            }
        }
    } else if ((sourcepiece == 'k') && (hozdist<-1)) {
        if (!curmove->castle_info[2]) {
            return 0;
        }
        for (i=0; i<5; i++) {
            if (square_threat(board, 7, i, BLACK_MOVE)) {
                return 0;
            }
        }
    } else if ((sourcepiece == 'k') && (hozdist>1)) {
        if (!curmove->castle_info[3]) {
            return 0;
        }
        for (i=5; i<BOARD_SIZE; i++) {
            if (square_threat(board, 7, i, BLACK_MOVE)) {
                return 0;
            }
        }
    }
    return 1;
}