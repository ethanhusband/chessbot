#include "Types.hh"
#include "Input.hh"
#include "Translate.hh"



/* Notes:
    - #defines faster than enum for BS_Index ? To check

    // verify input_string is input_type
    // 
*/
using namespace std;
// PGN or FEN should be passed via << in stdin
int main() {
    string input_type;
    string input_string;
    BoardState chessboard;
    get_input(&input_type, &input_string);
    // to finish:
    translateInputToBSC(input_string, input_type, &chessboard);

}

