//  bishop_class.h

#ifndef bishop_class_h
#define bishop_class_h

#include "far_moving_piece_class.h"

using namespace std;

// class for bishop
class bishop: public far_moving_piece {
public:
    // constructor
    bishop(colour_type input_colour): far_moving_piece(input_colour) {piece_design = "  ^  ";}
    
    // destructor
    ~bishop() {}
    
    // override the far-moving piece function for non-diagonal movements so these
    // are impossible for bishops
    void add_squares_horizontally_or_vertically(const chessboard &board, vector <int> &allowed_positions, const int position, const int direction, const bool direction_is_vertical) const {}
};

#endif /* bishop_class_h */
