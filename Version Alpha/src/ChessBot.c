/*
    ChessBot v1.0.0
    @author: Ethan Husband
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
#include "./IO_Files/ReadInput.h"
#include "./IO_Files/PrintBoard.h"
#include "./Utils/Operations.h"
#include "./Minimax/ComputeMove.h"


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
/* NOTE: VERSION ALPHA IS ENTIRELY UNFINISHED AND UNUSEABLE, JUST CONTAINING THE CONCEPT AND PIECES OF CODE */
/*       IT IS ESSENTIALLY A SKELETON OF THE IDEA, AN INCOMPLETE ATTEMPT AT ADAPTING A C BASED CHECKERS BOT TO CHESS  */

int main(int argc, char const *argv[]) {
    board_t board;
    copy_board(starting_board, board);
    move_t *curmove = create_move(NULL, NULL, 0, FALSE, SENTINEL);
    
    for (int i=0; i<TOTAL_CASTLES; i++) {
        /* Indicate every rook can castle at the beginning of the game */
        curmove->castle_info[i] = TRUE;
    }

#if RELAYING_GAME
    printf("STARTING POSITION:\n");
    print_board(board);
#endif

    /* Conditionally accept FEN input or MoveFile input */
#if FEN_INPUT
    /* Read FEN File */
#endif
#if !FEN_INPUT
    read_movesfile(board, curmove);
#endif

#if COMPUTING_MOVE
    play_round(board, moves, en_passent, en_passent_col, rook_info); 
#endif
    return 0;
}

/* REAME.md:  

CODEBASE STANDARDS:

    - All functions should include JavaDocs
    - All .c files should #include their complementary .h files
    - All #includes should stay in .h files
    - All .h files have conditional compilation #ifndef (to not compile twice)
    - Common properties of pieces are abstracted wherever possible
    - Most run-time optimised algorithms are preferenced wherever possible

ROADMAP / ALGORITHM OUTLINE

* Copy the starting board to the main board.
* Read a given FEN (VERSION 2) or MovesFile
    * DISQUALIFIABLE Ensure read moves are legal
* Implement legal move checking system
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

CURRENT PROGRESS (VERSION 1) :

* Copy the starting board to the main board.
* Read Movesfile
    * DISQUALIFIABLE Ensure read moves are legal
* DISQUALIFIABLE Implement legal move checking system
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