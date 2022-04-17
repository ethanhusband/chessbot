#include "Threats.h"
#include "Types.h"
#include "Macros.h"

int square_threats(board_t board, int row, int col, int player) {
    /* Calculate the amount of pieces from one team threatening a square */
    int i, j, mover=player%CHECK_MOVE, threats=0, m, n;
    char curpiece;
    for (i=0; i<BOARD_SIZE; i++) {
        for (j=0; j<BOARD_SIZE; j++) {
            curpiece = board[i][j];
            if (((mover==WHITE_MOVE) && (isupper(curpiece))) || ((mover==BLACK_MOVE) && (islower(curpiece)))) {
                /* Check if white pawn poses a threat */
                    if (curpiece == WHITE_PAWN) {
                        if ((i+1==row) && ((j+1 == col) || (j-1)==col)) {
                            threats++;
                        } 
                /* Check if black pawn poses threat */
                    } else if (curpiece == BLACK_PAWN) {
                        if ((i-1==row) && ((j+1 == col) || (j-1)==col)) {
                            threats++;
                        } 
                /* Check if knight poses a threat */
                    } else if ((curpiece == WHITE_KNIGHT) || (curpiece == BLACK_KNIGHT)) {
                        for (m=-2; m<=2; m++) {
                            for (n=-2; n<=2; n++) {
                                if ((m==0) || (n==0) || (m==n) || (m==-n)) {
                                    continue;
                                } else if ((i+m == row) && (j+n == col)) {
                                    threats++;
                                }
                            }
                        }
                    }
                /* Check if bishop poses a threat */
                    } else if ((curpiece == WHITE_BISHOP) || (curpiece == BLACK_BISHOP)) {
                        for (m=0; m<BOARD_SIZE; m++) {
                            if (((i+m == row) && (j+m == col)) || \
                                ((i+m == row) && (j-m == col)) || \
                                ((i-m == row) && (j+m == col)) || \
                                ((i-m == row) && (j-m == col))) {
                                threats++;
                            }
                        }
                /* Check if rook poses threat */
                    } else if ((curpiece == WHITE_ROOK) || (curpiece == BLACK_ROOK)) {
                        for (m=0; m<BOARD_SIZE; m++) {
                            if (((i+m == row) && (j == col)) || \
                                ((i-m == row) && (j == col)) || \
                                ((i == row) && (j+m == col)) || \
                                ((i == row) && (j-m == col))) {
                                threats++;
                            }
                        }
                /* Check if queen poses threat */
                    } else if ((curpiece == WHITE_QUEEN) || (curpiece == BLACK_QUEEN)) {
                        for (m=0; m<BOARD_SIZE; m++) {
                            if (((i+m == row) && (j+m == col)) || \
                                ((i+m == row) && (j-m == col)) || \
                                ((i-m == row) && (j+m == col)) || \
                                ((i-m == row) && (j-m == col)) || \
                                ((i+m == row) && (j == col)) || \
                                ((i-m == row) && (j == col)) || \
                                ((i == row) && (j+m == col)) || \
                                ((i == row) && (j-m == col))) {
                                threats++;
                            }
                        }
                    } else if (curpiece == WHITE_KING) {
                        m=1;
                        if (((i+m == row) && (j+m == col)) || \
                            ((i+m == row) && (j-m == col)) || \
                            ((i-m == row) && (j+m == col)) || \
                            ((i-m == row) && (j-m == col)) || \
                            ((i+m == row) && (j == col)) || \
                            ((i-m == row) && (j == col)) || \
                            ((i == row) && (j+m == col)) || \
                            ((i == row) && (j-m == col))) {
                            threats++;
                        }
                    }
        }
    }
    return threats;
}