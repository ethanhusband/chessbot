#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <strings.h>
#include <limits.h>

/* MACROS (NOT MAKRIS) */

/* The reading constants */
#define BOARD_SIZE 8
#define SENTINEL -1
#define CELL_ORDINATES 2
#define CHECK_MOVE 2
#define BLACK_MOVE 0
#define WHITE_MOVE 1
/* where each of the move indexes are stored in a move vector */
#define SOURCE_ROW 0
#define SOURCE_COL 1
#define TARGET_ROW 2
#define TARGET_COL 3
#define WHITE_PAWN_ROW 1
#define BLACK_PAWN_ROW 6
#define PAWN_START_DIST 2
#define PAWN_MOVE_DIST 1
#define EN_PASSENTWROW 4
#define EN_PASSENTBROW 3
#define TOTAL_CASTLES 4

/* Eval bar constants */
#define PAWN_COST 100
#define KNIGHT_COST 300
#define BISHOP_COST 300
#define ROOK_COST 500
#define QUEEN_COST 900
#define KING_COST 1000000000

/* The board design */
#define EMPTY_CELL '.'
#define BLACK_PAWN 'p'
#define BLACK_KNIGHT 'n'
#define BLACK_BISHOP 'b'
#define BLACK_ROOK 'r'
#define BLACK_QUEEN 'q'
#define BLACK_KING 'k'

#define WHITE_PAWN 'P'
#define WHITE_KNIGHT 'N'
#define WHITE_BISHOP 'B'
#define WHITE_ROOK 'R'
#define WHITE_QUEEN 'Q'
#define WHITE_KING 'K'

#define ROW_SEPERATOR "   +---+---+---+---+---+---+---+---+\n"
#define MOVE_SEPERATOR "=====================================\n"
#define TEAM_PIECES 12
#define COLUMNS "     A   B   C   D   E   F   G   H\n"
#define PROGRAM_MOVE "*** "
#define READ_MOVE 0
#define COMPUTED_MOVE 1

/* The computation constants */
#define TREE_DEPTH 3
#define INITIAL_DEPTH 0
#define NO_OPTIONS 0
#define INITIAL_SIZE 20

/* TYPEDEFS */

typedef int castling_t[TOTAL_CASTLES];
typedef char board_t[BOARD_SIZE][BOARD_SIZE];
typedef int indexvector_t[CELL_ORDINATES*CELL_ORDINATES];
typedef char movechars_t[CELL_ORDINATES*CELL_ORDINATES];

typedef struct {
    indexvector_t vector;
    castling_t castle_info;
    int movenum, en_passent, en_passent_col;
    /* Note: en_passent TRUE indicates it is available, not that it has happened */
} move_t;

typedef struct node decision_node_t;
struct node {
    board_t board;
    int options, minimax_cost;
    move_t move;
    decision_node_t *next_move;
};

board_t starting_board = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, \
                          {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, \
                          {'.', '.', '.', '.', '.', '.', '.', '.'},\
                          {'.', '.', '.', '.', '.', '.', '.', '.'},\
                          {'.', '.', '.', '.', '.', '.', '.', '.'},\
                          {'.', '.', '.', '.', '.', '.', '.', '.'},\
                          {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},\
                          {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

    /* For caslting purposes */

/* FUNCTION PROTOTYPES */

int ctoi(char movenode);
int itoc(int movenode, int from);
void make_indexvector(movechars_t cvector, indexvector_t ivector);
void make_movechars(movechars_t cvector, indexvector_t ivector);
void copy_board(board_t b1, board_t b2);
void print_move(board_t board, int programmove, move_t *curmove);
void print_board(board_t board);

int read_input(board_t board, int *moves, int *Men_passent, \
                int *Men_passent_col, castling_t Mcastle_info);
void update_rooks(board_t board, move_t *curmove, castling_t rook_info);
void en_passent_available(board_t board, move_t *curmove, int *en_passent, int *en_passent_col);
void update_board(board_t board, move_t *move);
int promotion(board_t board, move_t curmove);
int en_passent_happened(board_t board, move_t *curmove);
int legal_input(board_t board, move_t *curmove);
int check_piece(board_t board, move_t *curmove);
int move_on_board(indexvector_t vector);
int capture_opposition(board_t board, move_t *curmove);
int pawn_legal(board_t board, move_t *curmove);
int rook_legal(board_t board, move_t *curmove);
int bishop_legal(board_t board, move_t *curmove);
int queen_legal(board_t board, move_t *curmove);
int knight_legal(board_t board, move_t *curmove);
int king_legal(board_t board, move_t *curmove);
int castling_happened(board_t board, move_t *curmove);
int castling_legal(board_t board, move_t *curmove);
int square_threat(board_t board, int row, int col, int player);

int material_cost(board_t board);
int positional_cost(board_t board);
double aggregate_cost(board_t board);

/* MAIN FUNCTION */

int main(int argc, char const *argv[]) {
    int moves = 0, en_passent, en_passent_col, i;
    board_t board;
    castling_t rook_info;
    copy_board(board, starting_board);
    printf("STARTING POSITION:\n");
    print_board(board);
    for (i=0; i<TOTAL_CASTLES; i++) {
        /* None of the rooks have castled yet */
        rook_info[i] = 1;
    }
    read_input(board, &moves, &en_passent, &en_passent_col, rook_info);
    play_round(board, moves, en_passent, en_passent_col, rook_info);
    return 0;
}

/* INPUT SECTION */

    /* OPERATIONS */
int ctoi(char movenode) {
    /* Convert a cell char to corresponding board_t index */
    /* Returns impossible SENTINEL if char invalid */
    int move_index;
    if ((movenode>='A') && (movenode<='H')) {
        move_index = (int)movenode - (int)'A';
    } else if ((movenode>='1') && (movenode<='8')) {
        move_index = (int)movenode - (int)'1';
    } else {
        /* This move must be invalid, so set the sentinel */
        move_index = SENTINEL;
    }
    return move_index;
}

int itoc(int movenode, int from) {
    assert((movenode>=0) && (movenode <= 7));
    /* If the index movenode is from was even, we need to convert to a row char, 
    otherwise col char, because of how the indexvector is structured */
    int rowflag = from%2;
    /* We are converting an index to a row character */
    if (rowflag==0) {
        return (char)(movenode + '1');
    } else {
        return (char)(movenode + 'A');
    }
}

void make_indexvector(movechars_t cvector, indexvector_t ivector) {
    /* Convert move vector represented in char into int representation */
    /* Note: the row/col positions are inverted for the char vector */
    ivector[SOURCE_ROW] = ctoi(cvector[SOURCE_ROW]);
    ivector[SOURCE_COL] = ctoi(cvector[SOURCE_COL]);
    ivector[TARGET_ROW] = ctoi(cvector[TARGET_ROW]);
    ivector[TARGET_COL] = ctoi(cvector[TARGET_COL]);
}

void make_movechars(movechars_t cvector, indexvector_t ivector) {
    /* Convert move vector represented in int into char representation */
    cvector[SOURCE_ROW] = itoc(ivector[SOURCE_ROW], SOURCE_ROW);
    cvector[SOURCE_COL] = itoc(ivector[SOURCE_COL], SOURCE_COL);
    cvector[TARGET_ROW] = itoc(ivector[TARGET_ROW], TARGET_ROW);
    cvector[TARGET_COL] = itoc(ivector[TARGET_COL], TARGET_COL);
}

void copy_board(board_t b1, board_t b2) {
    /* Copy board 2 to board 1 */
    int i, j;
    for (i=0; i<BOARD_SIZE; i++) {
        for (j=0; j<BOARD_SIZE; j++) {
            b1[i][j] = b2[i][j];
        }
    }
}

        /* Not done - need eval bar */
void print_move(board_t board, int programmove, move_t *curmove) {
    /* Print the current move */
    movechars_t output;
    make_movechars(output, curmove->vector);
    printf(MOVE_SEPERATOR);
    /* Check if we're reading a move or the program is playing it */
    if (programmove) {
        printf(PROGRAM_MOVE);
    }
    /* Check if black or white move (given white starts) */
    if (curmove->movenum%CHECK_MOVE==WHITE_MOVE) {
        printf("WHITE ACTION #%d: ", curmove->movenum);
    } else {
        printf("BLACK ACTION #%d: ", curmove->movenum);
    }
    printf("%c moves %c%c-%c%c\n", board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]], \
                output[SOURCE_COL], output[SOURCE_ROW], \
                output[TARGET_COL], output[TARGET_ROW]);
    printf("MATERIAL COST: %d\n", material_cost(board)/100);
    /* NOT FINISHED */
    printf("POSITIONAL COST: %d\n", positional_cost(board)/100);
    printf("AGGREGATE SCALED COST: %.1lf\n", aggregate_cost(board));
    /* NOT FINISHED */
    print_board(board);
}

void print_board(board_t board) {
    /* Print the current game board */
    int i, j;
    for (i=BOARD_SIZE-1; i>=0; i--) {
        printf(ROW_SEPERATOR);
        /* Print the current row number on the side */
        printf(" %d |", i+1);
        /* Print every item in that row */
        for (j=0; j<BOARD_SIZE; j++) {
            printf(" %c |", board[i][j]);
        }
        putchar('\n');
    }
    printf(ROW_SEPERATOR);
    printf(COLUMNS);
}

    /* READING MOVES */

int read_input(board_t board, int *moves, int *Men_passent, int *Men_passent_col, castling_t Mcastle_info) {
    /* Interpret the input, update the board.
    Return 1 if input is valid, 0 otherwise */
    int en_passent=0, en_passent_col=SENTINEL, i;
    char sourcepiece;
    movechars_t cvector;
    indexvector_t ivector;
    move_t *curmove;
    while (scanf("%c%c-%c%c\n", &cvector[SOURCE_COL], &cvector[SOURCE_ROW], \
            &cvector[TARGET_COL], &cvector[TARGET_ROW]) != EOF) { 
        (*moves)++;

        printf("MOVE READ: %c%c-%c%c\n", cvector[SOURCE_COL], cvector[SOURCE_ROW], cvector[TARGET_COL], cvector[TARGET_ROW]);
        make_indexvector(cvector, ivector);
        printf("MOVE CONVERTED: %d,%d-%d,%d\n", ivector[SOURCE_ROW], ivector[SOURCE_COL], ivector[TARGET_ROW], ivector[TARGET_COL]);

        curmove=(move_t*)malloc(sizeof(move_t));
        for (i=0; i<CELL_ORDINATES*CELL_ORDINATES; i++) {
            curmove->vector[i] = ivector[i];
        }
        curmove->movenum = *moves;
        curmove->en_passent = en_passent; 
        curmove->en_passent_col = en_passent_col;
        for (i=0; i<TOTAL_CASTLES; i++) {
            curmove->castle_info[i] = Mcastle_info[i];
        }
        /* Ensure the input is legal */
        if (!legal_input(board, curmove)) {
            printf("TERMINATED: ILLEGAL INPUT\n");
            return 0;
        }
        /* Update which rooks can still castle */
        sourcepiece = board[ivector[SOURCE_ROW]][ivector[SOURCE_COL]];
        if ((sourcepiece == WHITE_ROOK) || (sourcepiece == BLACK_ROOK)) {
            update_rooks(board, curmove, Mcastle_info);
        }
        /* En Passent is read to local variables after computing legality.
        This computation is then used to assign the en_passent values next round */
        en_passent_available(board, curmove, &en_passent, &en_passent_col);
        update_board(board, curmove);
        print_move(board, READ_MOVE, curmove);
        free(curmove);
    }
    *Men_passent = en_passent;
    *Men_passent_col = en_passent_col;
    return 1;
}

void update_rooks(board_t board, move_t *curmove, castling_t rook_info) {
    if ((curmove->vector[SOURCE_ROW] == 0) && (curmove->vector[SOURCE_COL] == 0)) {
        rook_info[0] = 0; 
    } else if ((curmove->vector[SOURCE_ROW] == 0) && (curmove->vector[SOURCE_COL] == 7)) {
        rook_info[1] = 0;
    } else if ((curmove->vector[SOURCE_ROW] == 7) && (curmove->vector[SOURCE_COL] == 0)) {
        rook_info[2] = 0;
    } else if ((curmove->vector[SOURCE_ROW] == 7) && (curmove->vector[SOURCE_COL] == 7)) {
        rook_info[3] = 0;
    }
}

void en_passent_available(board_t board, move_t *curmove, int *en_passent, int *en_passent_col) {
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    if ((sourcepiece == BLACK_PAWN) || (sourcepiece == WHITE_PAWN)) {
        if (abs(curmove->vector[SOURCE_ROW] - curmove->vector[TARGET_ROW]) == PAWN_START_DIST) {
            *en_passent = 1;
            *en_passent_col = curmove->vector[SOURCE_COL];
        }
    } else {
        *en_passent = 0;
        *en_passent_col = SENTINEL;
    }
}

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
    if (promotion(board, curmove) {
        if (curmove->movenum%CHECK_MOVE == BLACK_MOVE)) {
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

int promotion(board_t board, move_t curmove) {
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    if ((curmove->movenum%CHECK_MOVE == WHITE_MOVE) && (sourcepiece == WHITE_PAWN) && (curmove->vector[TARGET_ROW] == 7)) {
        return 1;
    } else if ((curmove%CHECK_MOVE == BLACK_MOVE) && (sourcepiece == WHITE_PAWN) && (curmove->vector[TARGET_ROW] == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int en_passent_happened(board_t board, move_t *curmove) {
    /* Assumes sourcepiece and board locations are correct */
    /* Return 1 if an en_passent capture happened, 0 otherwise */
    if (!curmove->en_passent) {
        return 0;
    }
    int move = curmove->movenum%CHECK_MOVE, vertdist=curmove->vector[TARGET_ROW]-curmove->vector[SOURCE_ROW],\
        hozdist=abs(curmove->vector[TARGET_COL]-curmove->vector[SOURCE_COL]);
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    /* Ensure move is even with the right piece */
    if ((sourcepiece != BLACK_PAWN) || (sourcepiece != WHITE_PAWN))  {
        return 0;
    /* Ensure capture is possible with piece, and move is diagonal */
    } else if ((curmove->vector[TARGET_COL] == curmove->en_passent_col) && (hozdist == 1)) {
        /* Ensure capture was with the right piece and of the opposition */
        if ((move==WHITE_MOVE) && (sourcepiece == WHITE_PAWN) && (curmove->vector[SOURCE_ROW] == EN_PASSENTWROW) && \
            (islower(board[curmove->vector[TARGET_ROW-1]][curmove->vector[TARGET_COL]])) && (vertdist == 1)) {
            return 1;
        } else if ((sourcepiece == BLACK_PAWN) && (curmove->vector[SOURCE_ROW] == EN_PASSENTWROW) && \
                    (isupper(board[curmove->vector[TARGET_ROW+1]][curmove->vector[TARGET_COL]])) && (vertdist == -1)) {
            return 1;
        }
    } 
    return 0;
}

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

int pawn_legal(board_t board, move_t *curmove) {
    /* Verify a pawn move is legal */
    /* Can assume it is on the board and source cells exist, assume not en_passent */
    int vertmovedist = abs(curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW]);
    int hozmovedist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]);
    char targetsquare = board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]];
    /* Ahead cell is empty */
    if (curmove->movenum%CHECK_MOVE==WHITE_MOVE) {
        /* Could be a two space move */
        if ((curmove->vector[SOURCE_ROW] == WHITE_PAWN_ROW) && (vertmovedist == PAWN_START_DIST) && \
                (targetsquare == '.') && (board[curmove->vector[TARGET_ROW]-1][curmove->vector[TARGET_COL]] == '.') && \
                (hozmovedist == 0)) {
            return 1;
        /* Could be a move one space ahead */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == 0) && (targetsquare == '.')) {
            return 1;
        /* Must be a capture, not en passent */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == PAWN_MOVE_DIST) && \
                    (islower(board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]]))) {
            return 1;
        } else {
            /* This must not be legal */
            return 0;
        }
    } else {
        /* Could be a two space move */
        if ((curmove->vector[SOURCE_ROW] == BLACK_PAWN_ROW) && (vertmovedist == PAWN_START_DIST) && \
                (targetsquare == '.') && (board[curmove->vector[TARGET_ROW]+1][curmove->vector[TARGET_COL]] == '.') && \
                (hozmovedist == 0)) {
            return 1;
        /* Could be a move one space ahead */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == 0) && (targetsquare == '.')) {
            return 1;
        /* Must be a capture, not en passent */
        } else if ((vertmovedist == PAWN_MOVE_DIST) && (hozmovedist == PAWN_MOVE_DIST) && \
                    (isupper(board[curmove->vector[TARGET_ROW]][curmove->vector[TARGET_COL]]))) {
            return 1;
        } else {
            /* This must not be legal */
            return 0;
        }
    }
}

int rook_legal(board_t board, move_t *curmove) {
    /* Detect legality of a rook move, assume not castling */
    int vertmovedist = curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW];
    int hozmovedist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL];
    int i;
    if ((vertmovedist == 0) && (hozmovedist >= 1)) {
        /* Horizontal positive path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_COL]+1; i<curmove->vector[TARGET_COL]; i++) {
            if (board[curmove->vector[SOURCE_ROW]][i] != '.') {
                return 0;
            }
        }
    } else if ((vertmovedist == 0) && (hozmovedist <= -1)) {
        /* Horizontal negative path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_COL]-1; i<curmove->vector[TARGET_COL]; i--) {
            if (board[curmove->vector[SOURCE_ROW]][i] != '.') {
                return 0;
            }
        }
    } else if ((vertmovedist == 0) && (hozmovedist >= 1)) {
        /* Vertical positive path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_ROW]+1; i<curmove->vector[TARGET_ROW]; i++) {
            if (board[i][curmove->vector[SOURCE_COL]] != '.') {
                return 0;
            }
        }
    } else if ((hozmovedist == 0) && (vertmovedist <= -1)) {
        /* Vertical negative path must be clear, dont need to check target square */
        for (i=curmove->vector[SOURCE_ROW]-1; i<curmove->vector[TARGET_ROW]; i--) {
            if (board[i][curmove->vector[SOURCE_COL]] != '.') {
                return 0;
            }
        }
    }
    return 1;
}

int bishop_legal(board_t board, move_t *curmove) {
    /* Detect legality of a bishop move */
    int i, hozdist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL], \
        vertdist = curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW];
    if ((vertdist == 0) || (hozdist == 0) || (abs(hozdist) != abs(vertdist))) {
        return 0;
    }
    /* Find vertical direction */
    if (vertdist>0) {
        vertdist=1;
    } else {
        vertdist=-1;
    }
    /* Find horizontal direction */
    if (hozdist>0) {
        hozdist=1;
    } else {
        hozdist=-1;
    }
    /* Ensure no spaces in between target are occupied */
    for (i=1; i<abs(hozdist); i++) {
        if (board[curmove->vector[SOURCE_ROW]+i*vertdist][curmove->vector[SOURCE_COL]+i*hozdist] != '.') {
            return 0;
        }
    }
    return 1;
}

int queen_legal(board_t board, move_t *curmove) {
    /* Detect legality of a queen move */
    int hozdist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL], \
        vertdist = curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW];
    /* Can simply be reduced to bishop or rook case */
    if ((hozdist == 0) || (vertdist == 0)) {
        printf("CHECKING ROOK\n");
        return rook_legal(board, curmove);
    } else {
        return bishop_legal(board, curmove);
    }
}

int knight_legal(board_t board, move_t *curmove) {
    /* Detect legality of knight move */
    int hozdist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]), \
        vertdist = abs(curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW]);
    /* Cause it can jump this is easy to check, just ensure it moves the right distance */
    if (!(((vertdist == 2) && (hozdist == 1)) || ((vertdist == 1) && (hozdist == 2)))) {
        return 0;
    } else {
        return 1;
    }
}

int king_legal(board_t board, move_t *curmove) {
    int hozdist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]), \
        vertdist = abs(curmove->vector[TARGET_ROW] - curmove->vector[SOURCE_ROW]);
    if (castling_happened(board, curmove)) {
        return castling_legal(board, curmove);
    } else if (!(hozdist==1 || vertdist==1)) {
        return 0;
    }
    return 1;
}

int castling_happened(board_t board, move_t *curmove) {
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    int hozdist = abs(curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL]);
    if ((sourcepiece == 'K') && (hozdist == 2)) {
        return 1;
    } else {
        return 0;
    }
}

int castling_legal(board_t board, move_t *curmove) {
    /* Castling is represented uniquely as a king move of length 2, 
    which we can assume is already true */
    char sourcepiece = board[curmove->vector[SOURCE_ROW]][curmove->vector[SOURCE_COL]];
    int hozdist = curmove->vector[TARGET_COL] - curmove->vector[SOURCE_COL], i;
    if ((sourcepiece == 'K') && (hozdist<-1)) {
        if (!curmove->castle_info[0]) {
            return 0;
        }
        for (i=0; i<5; i++) {
            if (square_threat(board, 0, i, BLACK_MOVE)) {
                return 0;
            }
        }
    } else if ((sourcepiece == 'K') && (hozdist>1)) {
        if (!curmove->castle_info[1]) {
            return 0;
        }
        for (i=4; i<BOARD_SIZE; i++) {
            if (square_threat(board, 0, i, BLACK_MOVE)) {
                return 0;
            }
        }
    } else if ((sourcepiece == 'k') && (hozdist<-1)) {
        if (!curmove->castle_info[2]) {
            return 0;
        }
        for (i=0; i<5; i++) {
            if (square_threat(board, 7, i, BLACK_MOVE)) {
                return 0;
            }
        }
    } else if ((sourcepiece == 'k') && (hozdist>1)) {
        if (!curmove->castle_info[3]) {
            return 0;
        }
        for (i=5; i<BOARD_SIZE; i++) {
            if (square_threat(board, 7, i, BLACK_MOVE)) {
                return 0;
            }
        }
    }
    return 1;
}

int square_threat(board_t board, int row, int col, int player) {
    /* Calculate the amount of pieces from one team threatening a square */
    int i, j, mover=player%CHECK_MOVE, threats=0, m, n;
    char curpiece;
    for (i=0; i<BOARD_SIZE; i++) {
        for (j=0; j<BOARD_SIZE; j++) {
            curpiece = board[i][j];
            if (((mover==WHITE_MOVE) && (isupper(curpiece))) || ((mover==BLACK_MOVE) && (islower(curpiece)))) {
                /* Check if white pawn poses a threat */
                    if (curpiece == WHITE_PAWN) {
                        if ((i+1==row) && ((j+1 == col) || (j-1)==col)) {
                            threats++;
                        } 
                /* Check if black pawn poses threat */
                    } else if (curpiece == BLACK_PAWN) {
                        if ((i-1==row) && ((j+1 == col) || (j-1)==col)) {
                            threats++;
                        } 
                /* Check if knight poses a threat */
                    } else if ((curpiece == WHITE_KNIGHT) || (curpiece == BLACK_KNIGHT)) {
                        for (m=-2; m<=2; m++) {
                            for (n=-2; n<=2; n++) {
                                if ((m==0) || (n==0) || (m==n) || (m==-n)) {
                                    continue;
                                } else if ((i+m == row) && (j+n == col)) {
                                    threats++;
                                }
                            }
                        }
                    }
                /* Check if bishop poses a threat */
                    } else if ((curpiece == WHITE_BISHOP) || (curpiece == BLACK_BISHOP)) {
                        for (m=0; m<BOARD_SIZE; m++) {
                            if (((i+m == row) && (j+m == col)) || \
                                ((i+m == row) && (j-m == col)) || \
                                ((i-m == row) && (j+m == col)) || \
                                ((i-m == row) && (j-m == col))) {
                                threats++;
                            }
                        }
                /* Check if rook poses threat */
                    } else if ((curpiece == WHITE_ROOK) || (curpiece == BLACK_ROOK)) {
                        for (m=0; m<BOARD_SIZE; m++) {
                            if (((i+m == row) && (j == col)) || \
                                ((i-m == row) && (j == col)) || \
                                ((i == row) && (j+m == col)) || \
                                ((i == row) && (j-m == col))) {
                                threats++;
                            }
                        }
                /* Check if queen poses threat */
                    } else if ((curpiece == WHITE_QUEEN) || (curpiece == BLACK_QUEEN)) {
                        for (m=0; m<BOARD_SIZE; m++) {
                            if (((i+m == row) && (j+m == col)) || \
                                ((i+m == row) && (j-m == col)) || \
                                ((i-m == row) && (j+m == col)) || \
                                ((i-m == row) && (j-m == col)) || \
                                ((i+m == row) && (j == col)) || \
                                ((i-m == row) && (j == col)) || \
                                ((i == row) && (j+m == col)) || \
                                ((i == row) && (j-m == col))) {
                                threats++;
                            }
                        }
                    } else if (curpiece == WHITE_KING) {
                        m=1;
                        if (((i+m == row) && (j+m == col)) || \
                            ((i+m == row) && (j-m == col)) || \
                            ((i-m == row) && (j+m == col)) || \
                            ((i-m == row) && (j-m == col)) || \
                            ((i+m == row) && (j == col)) || \
                            ((i-m == row) && (j == col)) || \
                            ((i == row) && (j+m == col)) || \
                            ((i == row) && (j-m == col))) {
                            threats++;
                        }
                    }
        }
    }
    return threats;
}

    /* EVAL BAR */
int material_cost(board_t board) {
    int i, j, cost=0;
    char curpiece;
    for (i=0; i<BOARD_SIZE; i++) {
        for (j=0; j<BOARD_SIZE; j++) {
            curpiece = board[i][j];
            if (curpiece == EMPTY_CELL) {
                continue;
            } else if (curpiece == WHITE_PAWN) {
                cost+=PAWN_COST;
            } else if (curpiece == WHITE_KNIGHT) {
                cost+=KNIGHT_COST;
            } else if (curpiece == WHITE_BISHOP) {
                cost+=BISHOP_COST;
            } else if (curpiece == WHITE_ROOK) {
                cost+=ROOK_COST;
            } else if (curpiece == WHITE_QUEEN) {
                cost+=QUEEN_COST;
            } else if (curpiece == WHITE_KING) {
                cost+=KING_COST;
            } else if (curpiece == BLACK_PAWN) {
                cost-=PAWN_COST;
            } else if (curpiece == BLACK_KNIGHT) {
                cost-=KNIGHT_COST;
            } else if (curpiece == BLACK_BISHOP) {
                cost-=BISHOP_COST;
            } else if (curpiece == BLACK_ROOK) {
                cost-=ROOK_COST;
            } else if (curpiece == BLACK_QUEEN) {
                cost-=QUEEN_COST;
            } else if (curpiece == BLACK_KING) {
                cost-=KING_COST;
            }
        }
    }
    return cost;
}

    /* Not yet implemented */
int positional_cost(board_t board) {
    /* Bishops on open diagonals: scale 5 */
    /* Rooks on open files: scale 10 */
    /* Rooks connected: scale 5 */
    /* Rook ranks: scale 10 */
    /* King protected: scale 10 */
    /* Knights on outposts: scale 10 */
    /* Pawn structure: scale 5 */
    /* Passed pawn: scale depends on how far into the game */
    /* Centre occupation: scale 5 */
    /* Centre threats: scale 10 */
    /* F7 / equivalent squares */
    return 0;
}

double aggregate_cost(board_t board) {
    return (positional_cost(board)+material_cost(board))/100;
}

/* OUTPUT SECTION */

int play_round(board_t board, int move, int en_passent, int en_passent_col, castling_t rook_info) {
    /* Play a round of the game, return 0 if game over, 1 otherwise */
    decision_node_t *root=malloc(sizeof(decision_node_t));
    move_t *best_move=malloc(sizeof(move_t));
    copy_board(root->board, board);
    recursive_addlayers(root, move, INITIAL_DEPTH);
    find_move(root, best_move);
    best_move->movenum = move;

    /* Ensure legal move as a precaution */
    if (!legal_input(board, *best_move)) {
        free(best_move); recursive_free(root); free(root);
        printf("ERROR: Illegal action.\n");
        return 0;
    }
    update_board(board, *best_move);
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

void calculate_options(decision_node_t *node) {
    /* Fill the array of possible move options for a board */
    int i, j, index=0, cursize=INITIAL_SIZE;
    decision_node_t *possible_moves=malloc(INITIAL_SIZE*sizeof(decision_node_t));
    move_t last = node->move;
    assert(possible_moves != NULL);
    char curpiece;
    for (i=0; i<BOARD_SIZE; i++) {
        for (j=0; j<BOARD_SIZE; j++) {
            /* Add possibilities */
            curpiece = node->board[i][j];
            if ((node->move.movenum)%CHECK_MOVE==WHITE_MOVE) {
                /* It must be white's move */
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
                }
            } else if ((curpiece != EMPTY_CELL) || (islower(curpiece))) {
                /* Must be black's move */
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
                }
            }
        }
    }
    node->options = index;
    node->next_move = possible_moves;
}

void expand_array(decision_node_t possible_moves, int index, int *cursize) {
    if (index>=cursize) {
        /* Enlarge our options array if many */
        *cursize = 2*(*cursize);
        possible_moves = realloc(possible_moves, (*cursize)*sizeof(decision_node_t));
        assert(possible_moves != NULL);
    }
}

move_t *get_movenode() {
    
}

void add_w_pawn_options(move_t *last, decision_node_t *possible_moves, int i, int j, int *index, int *cursize) {
    move_t *new=(move_t*)malloc(sizeof(move_t));
    int i, needmovenode=0;
    if ((last->en_passent) && (abs(j-last->en_passent_col) == 1) && (i == EN_PASSENTWROW)) {
        new->vector[SOURCE_ROW]=i; new->vector[SOURCE_COL]=j; new->vector[TARGET_ROW]=i+1; new->vector[TARGET_COL]=last->en_passent_col;
        for (i=0; i<TOTAL_CASTLES; i++) {
            new->castle_info[i] = last->castle_info[i];
        }
        new->en_passent = 0; new->en_passent_col = SENTINEL;
        new->movenum = last->movenum + 1;
        needmovenode=1;
        possible_moves[(*index)++] = create_move(last->board, new);
    } 
    expand_array(possible_moves, index, cursize);
    if (needmovenode) {

    }
}


/* NOT YET APPLICABLE */
decision_node_t* create_move(board_t board, move_t move) {
    decision_node_t *newnode=malloc(sizeof(decision_node_t));
    copy_board(newnode->board, board);

    update_board(newnode->board, move);
    newnode->next_move = NULL;
    /* Note: Movenum will be updated at the start of the recursive call */
    newnode->move = move;
    return newnode;
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

/* Currently the program will:

* Copy the starting board to the main board.
* Read the moves
* Ensure read moves are legal 
* Print the moves
* Print the material cost of the board



*/