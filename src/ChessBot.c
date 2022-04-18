/*
    ChessBot v1.0.0
    @author: Ethan Husband
*/

/* TO DO
    * Fix all #includes to work without include path modifications
    * Move all #includes to header files
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <strings.h>
#include <limits.h>
#include "./Utils/Types.h"
#include "./Utils/Macros.h"
#include "./IO Files/ReadInput.h"
#include "./IO Files/PrintBoard.h"
#include "./Utils/Operations.h"


/* STARTING BOARD */
board_t starting_board = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, \
                        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, \
                        {'.', '.', '.', '.', '.', '.', '.', '.'},\
                        {'.', '.', '.', '.', '.', '.', '.', '.'},\
                        {'.', '.', '.', '.', '.', '.', '.', '.'},\
                        {'.', '.', '.', '.', '.', '.', '.', '.'},\
                        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},\
                        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};


/* MAIN FUNCTION */

int main(int argc, char const *argv[]) {
    /* Store variables with the number of moves in the game,
        whether en_passent just occurred, the column it just occurred in */
    int moves = 0, en_passent, en_passent_col;
    board_t board;
    castling_t rook_info;
    copy_board(starting_board, board);
    printf("STARTING POSITION:\n");
    /*
    print_board(board);
    
    for (int i=0; i<TOTAL_CASTLES; i++) {
        rook_info[i] = 1;
    }
    read_movesfile(board, &moves, &en_passent, &en_passent_col, rook_info);
    play_round(board, moves, en_passent, en_passent_col, rook_info); */
    return 0;
}

/* REAME.md:  

CODEBASE STANDARDS:

    - All functions should include JavaDocs
    - All .c files should #include their complementary .h files
    - Abstract common properties of pieces wherever possible
    - Implement the most run-time optimised algorithms possible

ROADMAP / ALGORITHM OUTLINE

* Copy the starting board to the main board.
* Read a given FEN
    * DISQUALIFIABLE Ensure read moves are legal
* Implement generalised and efficient legal move checking system
* Create minimax tree that works for specified depth
    * Create eval bar
        * Material cost
        * (VERSION 2) Positional cost
        * (VERSION 2) Aggregate cost
        * (VERSION 3) Implement NUEE neural network evaluation function
            * Implement reinforcement learning algorithm
    * Generate all possible move options for the layer below 
    * (VERSION 2) Alpha-Beta Pruning
    * (VERSION 3) Transposition Tables
        * ? Board Symmetries
    * ? Bitboards (Represent board with FEN)
    * ? Use endgame database
* DISQUALIFIABLE Print each move
    * Print whose move it is, cost, board, move that occurred, whether game is over

CURRENT PROGRESS :

* Copy the starting board to the main board.
* 
    * DISQUALIFIABLE Ensure read moves are legal
* 
* 
    * 
        * 
        * 
        * 
        * 
            * 
    *  
    * 
    * 
        * 
    * 
    * 
* DISQUALIFIABLE Print each move
    * Print whose move it is, cost, board, move that occurred, whether game is over

*/