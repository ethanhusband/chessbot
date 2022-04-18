#include "Legal.h"

int legal_input(board_t board, move_t *curmove) {
    /* Stop the program if any input is illegal */
    char sourcepiece=board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    int move = curmove->movenum%CHECK_MOVE;
    /* Check move is on the board */
    printf("MOVENUM: %d, SOURCEPIECE %c\n", move, sourcepiece);
    if (!move_on_board(curmove->vector)) {
        printf("ERROR: Move is not on the board.\n");
        return 0;
    /* Check sourcepiece exists and is current player's piece */
    } 
    if (sourcepiece == '.') {
        printf("ERROR: Source does not contain a piece.\n");
        return 0;
    /* Check if we're capturing */
    } 
    if (((move==WHITE_MOVE) && (islower(sourcepiece))) || ((move==BLACK_MOVE) && (isupper(sourcepiece)))) {
        printf("ERROR: Source contains opponent's piece.\n");
        return 0;
    } 
    if ((board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]] != '.') || \
                (en_passent_happened(board, curmove))) {
        if (!capture_opposition(board, curmove)) {
            printf("ERROR: Move does not capture opponent's piece or is invalid En Passent.\n");
            return 0;
        }
    /* Check the move specific to that piece is valid */
    } 
    if (!check_piece(board, curmove)) {
        return 0;
    }
    return 1;
}
/* BEWARE WHEN PIECE PINNED TO KING ? */

int check_piece(board_t board, move_t *curmove) {
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    /* Check the pawn */
    if ((sourcepiece == WHITE_PAWN) || (sourcepiece == BLACK_PAWN)) {
        if (!pawn_legal(board, curmove)) {
            printf("ERROR: Pawn move illegal.");
            return 0;
        } else {
            return 1;
        }
    /* Check the knight */
    } else if ((sourcepiece == WHITE_KNIGHT) || (sourcepiece == BLACK_KNIGHT)) {
        if (!knight_legal(board, curmove)) {
            printf("ERROR: Knight move illegal.");
            return 0;
        } else {
            return 1;
        }
    /* Check the bishop */
    } else if ((sourcepiece == WHITE_BISHOP) || (sourcepiece == BLACK_BISHOP)) {
        if (!bishop_legal(board, curmove)) {
            printf("ERROR: Bishop move illegal.");
            return 0;
        } else {
            return 1;
        }
    /* Check the rook */
    } else if ((sourcepiece == WHITE_ROOK) || (sourcepiece == BLACK_ROOK)) {
        if (!rook_legal(board, curmove)) {
            printf("ERROR: Rook move illegal.");
            return 0;
        } else {
            return 1;
        }
    /* Check the queen */
    } else if ((sourcepiece == WHITE_QUEEN) || (sourcepiece == BLACK_QUEEN)) {
        if (!queen_legal(board, curmove)) {
            printf("ERROR: Queen move illegal.");
            return 0;
        } else {
            return 1;
        }
    } else if ((sourcepiece == WHITE_KING) || (sourcepiece == BLACK_KING)) {
        if (!king_legal(board, curmove)) {
            printf("ERROR: King move illegal.");
            return 0;
        } else {
            return 1;
        }
    }
    /* The pieces must be labelled wrong or using source piece */
    printf("POTENTIAL PIECE LABELLING ERROR\n");
    return 0;
}

int move_on_board(indexvector_t vector) {
    /* Ensure every cell referenced is on the board */
    int i;
    for (i=0; i<CELL_ORDINATES+CELL_ORDINATES; i++) {
        if (vector[i] == SENTINEL) {
            return 0;
        }
    }
    return 1;
}

int capture_opposition(board_t board, move_t *curmove) {
    /* Ensure a capture is of an opposing piece */
    if (en_passent_happened(board, curmove)) {
        return 1;
    } 
    if (curmove->movenum%CHECK_MOVE == WHITE_MOVE) {
        if (islower(board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]])) {
            return 1;
        }
    } else {
        if (isupper(board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]])) {
            return 1;
        }
    }
    return 0;
}

/* NOT YET APPLICABLE */
int game_over(decision_node_t *root) {
    /* Check if the game is over, returning who won if so */
    if (root->options == NO_OPTIONS) {
        /* The game must be over if there are no available moves */
        if (root->move.movenum%CHECK_MOVE == BLACK_MOVE) {
            return INT_MAX;
        } else {
            return INT_MIN;
        }
    } else {
        return 0;
    }
}