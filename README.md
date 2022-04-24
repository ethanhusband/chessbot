# chessbot

This bot aims to read a given movesFile or FEN and determine the best possible move using C++, 
neural networks, minimax trees and other more niche chess programming techniques which will be described in Notes.c

Version History:
    VERSION ALPHA - An incomplete attempt at adapting a checkersbot written in C to a chessbot
    VERSION BETA - Early stage C++ chess bot that does not yet have a neural network implementation



ROADMAP / ALGORITHM OUTLINE

    * Copy the starting board to the main board.
    * Read a given FEN
        *  Ensure read moves are legal
    * Implement generalised and efficient legal move checking system
    * Create minimax tree that works for specified depth
        * Create eval bar
            * Implement NUEE neural network evaluation function
                * Implement reinforcement learning algorithm
        * Generate all possible move options for the layer below 
        * (VERSION 2) Alpha-Beta Pruning
        * (VERSION 3) Transposition Tables
            
    * Print each move
        * Print whose move it is, cost, board, move that occurred, whether game is over

    POTENTIAL FUTURE ADDITIONS:
    * ? Board Symmetries
    * ? Bitboards (Represent board with FEN)
    * ? Use endgame database
