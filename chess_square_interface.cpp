//  chess_square_interface.cpp

#include "chess_square_interface.h"

// friend function for outputting content of a board square
ostream &operator << (ostream &os, object_at_square &board_square) {
    // add the piece design string to the ostream
    os << board_square.get_piece_design() << endl;
    
    // add the design for the base of a piece (if the colour_type is not none),
    // including the colour of the piece as a character ('b' or 'w')
    if (board_square.get_colour() == black) {cout << " /b\\ " << endl;}
    else if (board_square.get_colour() == white) {cout << " /w\\ " << endl;}
    
    //return the ostream
    return os;
}
