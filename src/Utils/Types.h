#ifndef TYPES_H_SEEN
#define TYPES_H_SEEN

#include "./Macros.h"

/* TYPEDEFS */

    typedef int Boolean;

    /* Array of length 4 where each index stores a boolean value regarding whether a castle has 'castled' yet or not */
    typedef int castling_t[TOTAL_CASTLES];

    /* 8x8 array containing characters which holistically represent the entire board */
    /* Which piece corresponds to which character can be found above in PIECE REPRESENTATION CONSTANTS */
    typedef char board_t[BOARD_SIZE][BOARD_SIZE];

    /* An index vector type is an array of 4 integers which represent positions relevant to some move_t */
    /* Each ordinate of a move is mapped to with SOURCE_ROW, SOURCE_COL, TARGET_ROW, TARGET_COL */
    typedef int indexvector_t[CELL_ORDINATES*CELL_ORDINATES];
    
    /* Index vector in terms of letter/number coordinates normally seen on a board */
    typedef char movechars_t[CELL_ORDINATES*CELL_ORDINATES];

    /* Data structure representing a given move. */
    /* Holds an index vector with SOURCE_ROW, SOURCE_COL, TARGET_ROW, TARGET_COL ordinates */
    /* Has castling_t array indicating which pieces have castled (shorter runtime at expense of data) */
    /* Contains the number move it is, whether en_passent is possible */
    typedef struct {
        indexvector_t vector;
        castling_t castle_info;
        int movenum, en_passent, en_passent_col;
        /* Note: en_passent TRUE indicates it is AVAILABLE, not that it has happened */
    } move_t;

    /* Recursive data structure for a node in the minimax decision tree. */
    /* Includes the 2D board array */
    /* Includes info on the previous move (move_t move) */
    /* Includes cost (eval) of position (minimax_cost)
    /* Includes array of available 'next move' options (next_move) and the size of this array (options) */
    typedef struct node decision_node_t;
    struct node {
        board_t board;
        int options, minimax_cost;
        move_t move;
        decision_node_t *next_move;
    };

#endif /* !TYPES_H_SEEN */