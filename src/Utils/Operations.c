#include "./Operations.h"

/* MISCELLANEOUS OPERATIONS ON THE PROJECTS DATA STRUCTURES */

    /** CTOI (char to index)
     * @brief - Convert a letter/number ordinate to corresponding board_t index ordinate
     * 
     * @param moveNode - A letter from A to H or number from 1 to 8
     * @return int - Index corresponding to alphanum ordinate. Returns impossible SENTINEL if char is invalid.
     */
    int ctoi(char moveNode) {
        int move_index;
        /* Convert letter ordinate to index */
        if ((moveNode>='A') && (moveNode<='H')) {
            move_index = (int)moveNode - (int)'A';

        /* Convert numeric ordinate to index */
        } else if ((moveNode>='1') && (moveNode<='8')) {
            move_index = (int)moveNode - (int)'1';

        /* This move must be invalid, so set the sentinel */
        } else {
            move_index = SENTINEL;
        }
        return move_index;
    }

    /** ITOC (index to char)
     * @brief - Converts an entry from an index_vector into a alphanumeric ordinate.
     *          Clever use is made of the index_vector's structure to determine whether to convert to letter or num
     * 
     * @param moveNode - A board_t index/ordinate taken from an index_vector
     * @param from - The index that was required to access movenode from an index_vector. Should be 0 to 3.
     * @return char - character representing the ordinate that the index corresponded to
     */
    char itoc(int moveNode, int from) {
        assert((moveNode>=0) && (moveNode <= 7));
        /* If 'from' is even, then we need to convert to a row char (letter),
        Since in index_vector, SOURCE_ROW and TARGET_ROW are stored at the even indexes. 
        Otherwise convert to col char (letter), because the reference must be SOURCE_COL or TARGET_COL */
        int rowFlag = from%2;
        /* We are converting an index to a row character */
        if (rowFlag==0) {
            return (char)(moveNode + '1');
        } else {
            return (char)(moveNode + 'A');
        }
    }

    /** MAKE_INDEXVECTOR
     * @brief - Instantiate the data of an index_vector with that from a movechars vector
     * 
     * @param cvector - Pointer to a movechars vector (representation of a move in alphanumeric coordinates)
     * @param ivector - Pointer to an index_vector
     */
    void make_indexvector(movechars_t cvector, indexvector_t ivector) {
        /* Convert move vector represented in char into int representation */
        /* Note: the row/col positions are inverted for the char vector */
        ivector[SOURCE_ROW] = ctoi(cvector[SOURCE_ROW]);
        ivector[SOURCE_COL] = ctoi(cvector[SOURCE_COL]);
        ivector[TARGET_ROW] = ctoi(cvector[TARGET_ROW]);
        ivector[TARGET_COL] = ctoi(cvector[TARGET_COL]);
    }

    /** MAKE_MOVECHARS (vector)
     * @brief - Instantiate the data of a movechars with that from an index_vector
     * 
     * @param cvector - Pointer to a movechars vector (representation of a move in alphanumeric coordinates)
     * @param ivector - Pointer to an index_vector
     */
    void make_movechars(movechars_t cvector, indexvector_t ivector) {
        /* Convert move vector represented in int into char representation */
        cvector[SOURCE_ROW] = itoc(ivector[SOURCE_ROW], SOURCE_ROW);
        cvector[SOURCE_COL] = itoc(ivector[SOURCE_COL], SOURCE_COL);
        cvector[TARGET_ROW] = itoc(ivector[TARGET_ROW], TARGET_ROW);
        cvector[TARGET_COL] = itoc(ivector[TARGET_COL], TARGET_COL);
    }

    /** COPY_BOARD
     * @brief - Copy board 2 onto board 1
     * 
     * @param new_board - (likely empty ) board to be written into
     * @param old_board - board to read data from
     */
    void copy_board(board_t old_board, board_t new_board) {
        /* Copy board 2 to board 1 */
        int i, j;
        for (i=0; i<BOARD_SIZE; i++) {
            for (j=0; j<BOARD_SIZE; j++) {
                new_board[i][j] = old_board[i][j];
            }
        }
    }

    /** UPDATE_BOARD
     * @brief - Interpret a given move by taking a move and board structure, then adding the move to the board
     * 
     * @param board - current board prior to the move described in curmove occurring
     * @param curmove - structure describing a given move
     */
    void update_board(board_t board, move_t *curmove) {
        /* Update the board, assuming valid input */
        if (en_passent_happened(board, curmove)) {
            /* Delete the piece below the target */
            if (curmove->movenum%CHECK_MOVE == WHITE_MOVE) {
                board[curmove->vector[TARGET_ROW-1]][curmove->vector[TARGET_COL]] = '.';
            } else {
                board[curmove->vector[TARGET_ROW+1]][curmove->vector[TARGET_COL]] = '.';
            }

        } else if (castling_happened(board, curmove)) {
            int castle_direction = curmove->vector[TARGET_COL]-curmove->vector[SOURCE_COL];
            char rook;
            if (castle_direction<-1) {
                rook = board[curmove->vector[SOURCE_ROW]][0];
                board[curmove->vector[SOURCE_ROW]][0] = '.';
                board[curmove->vector[SOURCE_ROW]][1] = '.';
                board[curmove->vector[SOURCE_ROW]][3] = rook;
            } else if (castle_direction>1) {
                rook = board[curmove->vector[SOURCE_ROW]][7];
                board[curmove->vector[SOURCE_ROW]][7] = '.';
                board[curmove->vector[SOURCE_ROW]][5] = rook;
            }
        }

        if (promotion(board, curmove)) {
            if (curmove->movenum%CHECK_MOVE == BLACK_MOVE) {
                board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]] = 'q';
            } else {
                board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]] = 'Q';
            }
        } else {
            board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]] = \
            board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
        }
        board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]] = '.';
    }

    void expand_array(decision_node_t *possible_moves, int index, int *cursize) {
        if (index>=cursize) {
            /* Enlarge our options array if many */
            *cursize = 2*(*cursize);
            possible_moves = realloc(possible_moves, (*cursize)*sizeof(decision_node_t));
            assert(possible_moves != NULL);
        }
    }

/* NOT YET APPLICABLE */
void recursive_free(decision_node_t *root) {
    /* Recursively free all the memory in a decision tree */
    int i;
    if (root) {
        for (i=0; i<(root->options); i++) {
            recursive_free(root->next_move+i);
        }
        free(root->next_move);
        root->next_move = NULL;
    }
}

/* NOT YET APPLICABLE 
decision_node_t* create_move(board_t board, move_t *move) {
    decision_node_t *newnode=malloc(sizeof(decision_node_t));
    copy_board(board, newnode->board);

    update_board(newnode->board, move);
    newnode->next_move = NULL;
    /* Note: Movenum will be updated at the start of the recursive call */ /*
    newnode->move = move;
    return newnode;
}
*/