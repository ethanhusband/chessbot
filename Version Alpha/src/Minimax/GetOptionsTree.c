#include "GetOptionsTree.h"

void calculate_options(decision_node_t *node) {
    /* Fill the array of possible move options for a board */
    int i, j, index=0, cursize=INITIAL_SIZE;
    decision_node_t *possible_moves=malloc(INITIAL_SIZE*sizeof(decision_node_t));
    move_t *last = node->move;
    assert(possible_moves != NULL);
    char curpiece;
    for (i=0; i<BOARD_SIZE; i++) {
        for (j=0; j<BOARD_SIZE; j++) {
            /* Add possibilities */
            curpiece = node->board[i][j];
            if ((node->move->movenum)%CHECK_MOVE==WHITE_MOVE) {
                /* It must be white's move */
                /* TO BE IMPLEMENTED
                if ((curpiece == EMPTY_CELL) || (isupper(curpiece))) {
                    continue;
                } else if (curpiece == WHITE_PAWN) {
                    add_wpawn_options(index);
                } else if (curpiece == WHITE_KNIGHT) {
                    add_knight_options(index);
                } else if (curpiece == WHITE_BISHOP) {
                    add_bishop_options(index);
                } else if (curpiece == WHITE_ROOK) {
                    add_rook_options(index); 
                } else if (curpiece == WHITE_QUEEN) {
                    add_bishop_options(index);
                    add_rook_options();
                } else if (curpiece == WHITE_KING) {
                    add_king_options();
                }*/
            } else if ((curpiece != EMPTY_CELL) || (islower(curpiece))) {
                /* Must be black's move */ /* TO BE IMPLEMENTED
                if (curpiece == BLACK_PAWN) {
                    add_bpawn_options();
                } else if (curpiece == BLACK_KNIGHT) {
                    add_knight_options();
                } else if (curpiece == BLACK_BISHOP) {
                    add_bishop_options();
                } else if (curpiece == BLACK_ROOK) {
                    add_rook_options(); 
                } else if (curpiece == BLACK_QUEEN) {
                    add_bishop_options();
                    add_rook_options();
                } else if (curpiece == BLACK_KING) {
                    add_king_options();
                } */
            }
        }
    }
    node->options = index;
    node->next_move = possible_moves;
}

/*
                    add_knight_options(index);
                    add_bishop_options(index);
                    add_rook_options(index); 
                    add_bishop_options(index);
                    add_rook_options();
                    add_king_options();
*/

#if EXCLUDED
void add_w_pawn_options(move_t *last, decision_node_t *possible_moves, int i, int j, int *index, int *cursize) {
    move_t *new=(move_t*)malloc(sizeof(move_t));
    int needmovenode=0;
    if ((last->can_en_passent) && (abs(j-last->en_passent_col) == 1) && (i == EN_PASSENTWROW)) {
        new->vector[SOURCE_ROW]=i; new->vector[SOURCE_COL]=j; new->vector[TARGET_ROW]=i+1; new->vector[TARGET_COL]=last->en_passent_col;
        for (int k=0; k<TOTAL_CASTLES; k++) {
            new->castle_info[k] = last->castle_info[k];
        }
        new->can_en_passent = 0; new->en_passent_col = SENTINEL;
        new->movenum = last->movenum + 1;
        needmovenode=1;
        /* ERROR possible_moves[(*index)++] = create_move(last->board, new); */
    } 
    expand_array(possible_moves, index, cursize);
    if (needmovenode) {

    }
}
#endif