#include "FindMinCost.h"

/* NOT YET APPLICABLE */
void recur_fill_costs(decision_node_t *root, int depth) {
    /* Propagate the costs all the way up the tree from TREE_DEPTH */
    int i;
    /* Ensure the game isnt over */
    if (root->options == NO_OPTIONS) {
        root->minimax_cost = game_over(root);
        return;
    }
    /* At TREE_DEPTH-1 we need to find cost of all TREE_DEPTH child nodes */
    if (depth == TREE_DEPTH-1) {
        for(i=0; i<root->options; i++) {
            if (game_over(root->next_move+i)) {
                (root->next_move+i)->minimax_cost = \
                game_over(root->next_move+i);
                continue;
            }
            (root->next_move+i)->minimax_cost = \
            calculate_cost((root->next_move+i)->board);
        }
        propagate_cost(root);
        return;
    /* Recursively propagate costs up through the non TREE_DEPTH nodes */
    } else {
        for(i=0; i<root->options; i++) {
            recur_fill_costs(root->next_move+i, depth+1);
        }
        propagate_cost(root);
    }
}

/* NOT YET APPLICABLE */
void propagate_cost(decision_node_t *root) {
    /* Return the max/min cost for the children of the current node */
    int propagated_cost, i;
    if (root->move.movenum%CHECK_MOVE == BLACK_MOVE) {
        propagated_cost = INT_MIN;
        /* It must be black's move, so find the max */
        for(i=0; i<root->options; i++) {
            if ((root->next_move+i)->minimax_cost > propagated_cost) {
                propagated_cost = (root->next_move+i)->minimax_cost;
            }
        }
    } else {
        /* White's move, so find the min */
        propagated_cost = INT_MAX;
        for(i=0; i<root->options; i++) {
            if ((root->next_move+i)->minimax_cost < propagated_cost) {
                propagated_cost = (root->next_move+i)->minimax_cost;
            }
        }
    }
    root->minimax_cost = propagated_cost;
}

