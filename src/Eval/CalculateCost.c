#include "CalculateCost.h"
#include "Types.h"
#include "Macros.h"

    /* CURRENTLY BEING USED AS EVAL BAR UNTIL PROPER*/
int material_cost(board_t board) {
    int i, j, cost=0;
    char curpiece;
    for (i=0; i<BOARD_SIZE; i++) {
        for (j=0; j<BOARD_SIZE; j++) {
            curpiece = board[i][j];
            if (curpiece == EMPTY_CELL) {
                continue;
            } else if (curpiece == WHITE_PAWN) {
                cost+=PAWN_COST;
            } else if (curpiece == WHITE_KNIGHT) {
                cost+=KNIGHT_COST;
            } else if (curpiece == WHITE_BISHOP) {
                cost+=BISHOP_COST;
            } else if (curpiece == WHITE_ROOK) {
                cost+=ROOK_COST;
            } else if (curpiece == WHITE_QUEEN) {
                cost+=QUEEN_COST;
            } else if (curpiece == WHITE_KING) {
                cost+=KING_COST;
            } else if (curpiece == BLACK_PAWN) {
                cost-=PAWN_COST;
            } else if (curpiece == BLACK_KNIGHT) {
                cost-=KNIGHT_COST;
            } else if (curpiece == BLACK_BISHOP) {
                cost-=BISHOP_COST;
            } else if (curpiece == BLACK_ROOK) {
                cost-=ROOK_COST;
            } else if (curpiece == BLACK_QUEEN) {
                cost-=QUEEN_COST;
            } else if (curpiece == BLACK_KING) {
                cost-=KING_COST;
            }
        }
    }
    return cost;
}

    /* Not yet implemented */
int positional_cost(board_t board) {
    /* Bishops on open diagonals: scale 5 */
    /* Rooks on open files: scale 10 */
    /* Rooks connected: scale 5 */
    /* Rook ranks: scale 10 */
    /* King protected: scale 10 */
    /* Knights on outposts: scale 10 */
    /* Pawn structure: scale 5 */
    /* Passed pawn: scale depends on how far into the game */
    /* Centre occupation: scale 5 */
    /* Centre threats: scale 10 */
    /* F7 / equivalent squares */
    return 0;
}

double aggregate_cost(board_t board) {
    return (positional_cost(board)+material_cost(board))/100;
}