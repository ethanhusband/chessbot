#include "Translate.hh"

void translateInputToBSC(string input_string, string input_type, BoardState *chessboard) {
    ArrayBoard tmpBoard = ArrayBoard(input_string, input_type);
    arrayToBitboards(tmpBoard, chessboard->board);
    /* need to decide schema first for these */
    // need castling info
    // need en passent square
    // need player turn
}



/* Arrayboard class skeleton credit: https://codereview.stackexchange.com/questions/251795/parsing-a-chess-fen */

enum ArrayBoardCastle
{  king_side, queen_side };

enum Color
{ white, black };

class ArrayBoard {
    public:
    /* ATTRIBUTES */
        Color turn; 
        string enPassentSquare;
        char board[BOARD_SIZE];
        bool castleRights[TOTAL_PLAYERS][CASTLING_SIDES];
    
    /* CONSTRUCTORS */
        /* ArrayBoard should always be instantiated with an FEN or PGN (PGN yet to be implemented) */
        ArrayBoard(const string input_string, const string input_type) {
            if (input_type == "FEN") {
                ArrayBoardFromFEN(input_string);
            } else if (input_type == "PGN") {
                // to be added
            }
        };

        // Constructor for PGN input
        void ArrayBoardFromPGN(const string& pgn) {
            
        };

        // Constructor for FEN input
        void ArrayBoardFromFEN(const string& fen) {
            const size_t size = fen.size();
            size_t i = 0;
            int index = 0;

            // parse the board first. space character indicates end of board
            for (; (i < size) && (fen[i] != ' '); i++) {
                /* skip FEN'next row' identifier */
                if (fen[i] == '/') 
                    continue;
                
                /* empty squares in FEN are indicated by a number that describes the amount of consecutive empty squares */
                if (isdigit(fen[i])) {
                    index += (fen[i] - '0'); // converts char digit to int. `5` to 5
                }
                /* must have a piece, so assign it to the board array */
                else {
                    board[index++] = fen[i];
                }
            }
            assert(index == BOARD_SIZE);

            // assign the turn 
            if (fen[i + 1] == FEN_WHITE_NAME) {
                turn = Color::white;
            } else {
                turn = Color::black;
            }

            // read castling rights
            /* 3 is gap size from board to castle rights description */
            for (i += 3; (i < size ) && (fen[i] != ' '); i++) {
                if (fen[i] == BLACK_KING)
                    castleRights[Color::black][ArrayBoardCastle::king_side] = true;

                else if (fen[i] == WHITE_KING)
                    castleRights[Color::white][ArrayBoardCastle::king_side] = true;

                else if (fen[i] == BLACK_QUEEN)
                    castleRights[Color::black][ArrayBoardCastle::queen_side] = true;

                else if (fen[i] == WHITE_QUEEN)
                    castleRights[Color::white][ArrayBoardCastle::queen_side] = true;
            }

            // identify en passent
            enPassentSquare = fen.substr(i + 1, 3);
        };
};




void arrayToBitboards(ArrayBoard arrayBoard, Bitboards bitboards) {
    for (int i=0;i<BOARD_SIZE;i++) {
        Bitboard binary = 1LL << i;

        /* Map an arrayBoard piece to its corresponding bitboard index */
        switch (arrayBoard.board[i]) {
            case ARR_WHITE_PAWN: bitboards[BS_INDEX::WHITE_PAWN]+=binary;
                break;
            case ARR_WHITE_KNIGHT: bitboards[BS_INDEX::WHITE_KNIGHT]+=binary;;
                break;
            case ARR_WHITE_BISHOP: bitboards[BS_INDEX::WHITE_BISHOP]+=binary;
                break;
            case ARR_WHITE_ROOK: bitboards[BS_INDEX::WHITE_ROOK]+=binary;
                break;
            case ARR_WHITE_QUEEN: bitboards[BS_INDEX::WHITE_QUEEN]+=binary;
                break;
            case ARR_WHITE_KING: bitboards[BS_INDEX::WHITE_KING]+=binary;
                break;
            case ARR_BLACK_PAWN: bitboards[BS_INDEX::BLACK_PAWN]+=binary;
                break;
            case ARR_BLACK_KNIGHT: bitboards[BS_INDEX::BLACK_KNIGHT]+=binary;
                break;
            case ARR_BLACK_BISHOP: bitboards[BS_INDEX::BLACK_BISHOP]+=binary;
                break;
            case ARR_BLACK_ROOK: bitboards[BS_INDEX::BLACK_ROOK]+=binary;
                break;
            case ARR_BLACK_QUEEN: bitboards[BS_INDEX::BLACK_QUEEN]+=binary;
                break;
            case ARR_BLACK_KING: bitboards[BS_INDEX::BLACK_KING]+=binary;
                break;
        }
        
    }
}