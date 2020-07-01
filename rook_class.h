//rook_class.h

#ifndef rook_class_h
#define rook_class_h

#include "far_moving_piece_class.h"
using namespace std;

// class for rook
class rook: public far_moving_piece {
public:
    // constructor
    rook(colour_type input_colour): far_moving_piece(input_colour) {piece_design = " [_] ";}
    
    // destructor
    ~rook() {}
    
    // override the function that adds squares diagonally so that it is unused
    void add_squares_diagonally(const chessboard &board, vector <int> &allowed_positions, const int position, const int direction, const bool direction_is_vertical) const {}
};

#endif /* rook_class_h */
