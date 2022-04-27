#include "Input.hh"

void get_input(string *input_type, string *input_string) {
    cout << "Welcome to Chessbot Version Beta\n";
    get_input_type(input_type);
    get_input_string(input_string, *input_type);
}

void get_input_type(string *input_type) {
    cout << "Indicate use of FEN or PGN, then press enter: ";
    cin >> *input_type;
    transform((*input_type).begin(), (*input_type).end(), (*input_type).begin(), ::toupper);
    assert(verify_input_type(*input_type));
}

bool verify_input_type(string input_type) {
    if (input_type.compare("pgn") + input_type.compare("fen") != 0) {
        cout << "Invalid input type, please restart and enter 'PGN' or 'FEN'";
        return false;
    } else {
        cout << "Input type verified as " << input_type;
        return true;
    }
}

void get_input_string(string *input_string, string input_type) {
    cout << "Paste the " << input_type << ", then press Enter:\n";
    cin >> *input_string;
    assert(verify_input_string(*input_string, input_type));
}

bool verify_input_string(string input_string, string input_type) {
    // verification to be added
    return true;
}