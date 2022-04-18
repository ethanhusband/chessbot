# chessbot

CODEBASE STANDARDS:

    - All functions should include JavaDocs
    - All .c files should #include their complementary .h files
    - All #includes should stay in .h files
    - All .h files have conditional compilation #ifndef (to not compile twice)
    - Common properties of pieces are abstracted wherever possible
    - Most run-time optimised algorithms are preferenced wherever possible

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