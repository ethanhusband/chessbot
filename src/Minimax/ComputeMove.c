#include "ComputeMove.h"

int play_round(board_t board, int move, int en_passent, int en_passent_col, castling_t rook_info) {
    /* Play a round of the game, return 0 if game over, 1 otherwise */
    decision_node_t *root=malloc(sizeof(decision_node_t));
    move_t *best_move=malloc(sizeof(move_t));
    copy_board(board, root->board);
    recursive_addlayers(root, move, INITIAL_DEPTH);
    find_move(root, best_move);
    best_move->movenum = move;

    /* Ensure legal move as a precaution */
    if (!legal_input(board, best_move)) {
        free(best_move); recursive_free(root); free(root);
        printf("ERROR: Illegal action.\n");
        return 0;
    }
    update_board(board, best_move);
    print_move(board, *best_move);
    free(best_move); recursive_free(root); free(root);
    return 1;
}

void recursive_addlayers(decision_node_t *node, int move, int tree_depth) {
    /* Add depth to the tree in a recursive call at a specified depth */
    int i;
    node->move.movenum = move;
    node->options = NO_OPTIONS;
    if (tree_depth>TREE_DEPTH) {
        return;
    }
    calculate_options(node);
    if (node->options != NO_OPTIONS) {
        for (i=0; i<(node->options); i++) {
            recursive_addlayers(node->next_move+i, move+1, tree_depth+1);
        }
    }
    return;
}



/* NOT YET APPLICABLE */
void find_move(decision_node_t *root, move_t *best_move) {
    /* Play the best move available using the minimax decision tree */
    int i;
    if (game_over(root)) {
        /* We're not going to find any moves, so can return early */
        root->move.movenum = game_over(root);
        return;
    }
    recur_fill_costs(root, INITIAL_DEPTH);
    propagate_cost(root);
    for (i=0; i<root->options; i++) {
        if ((root->next_move+i)->minimax_cost == root->minimax_cost) {
            *best_move = (root->next_move+i)->move;
            break;
        }
    }
}