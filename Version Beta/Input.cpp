#include "Types.hh"

void arrayToBitboards(ArrayBoard chessboard, BoardState bitboards) {
    for (int i=0;i<BOARD_SIZE;i++) {
        Bitboard binary = 1LL << i;
        BS_INDEX bitboardIndex;

        /* While this switch approach looks inefficient, there logically has to be a way of mapping
            each piece in a chessboard array to bitboard at some point, so is necessary */
        switch (chessboard[i/BOARD_WIDTH][i%BOARD_WIDTH]) {
            case ('P'): bitboardIndex = WHITE_PAWN;
                break;
            case 'N': bitboardIndex = WHITE_KNIGHT;
                break;
            case 'B': bitboardIndex = WHITE_BISHOP;
                break;
            case 'R': bitboardIndex = WHITE_ROOK;
                break;
            case 'Q': bitboardIndex = WHITE_QUEEN;
                break;
            case 'K': bitboardIndex = WHITE_KING;
                break;
            case 'p': bitboardIndex = BLACK_PAWN;
                break;
            case 'n': bitboardIndex = BLACK_KNIGHT;
                break;
            case 'b': bitboardIndex = BLACK_BISHOP;
                break;
            case 'r': bitboardIndex = BLACK_ROOK;
                break;
            case 'q': bitboardIndex = BLACK_QUEEN;
                break;
            case 'k': bitboardIndex = BLACK_KING;
                break;
        }
        bitboards[bitboardIndex]+=binary;
    }
}