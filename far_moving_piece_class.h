//  far_moving_piece_class.h

#ifndef far_moving_piece_class_h
#define far_moving_piece_class_h

#include <iostream>
#include "piece_base_class.h"


using namespace std;

// class derived from piece base class for pieces that can move for
// multiple squares in a direction (the queens, bishops and rooks)
class far_moving_piece: public piece {
public:
    // parameterised constructor
    far_moving_piece(colour_type input_colour): piece(input_colour) {}
    
    // function to find and return available moves for a far-moving piece by calling the square-adding functions
    vector <int> default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const;
    
    // virtual function to work out available moves in a horizontal or direction for use in possible moves function
    virtual void add_squares_horizontally_or_vertically(const chessboard &board, vector <int> &allowed_positions, const int position, const int direction, const bool direction_is_vertical) const;
    
    // virtual function to work out available moves for diagonally moving pieces for use in possible moves function
    virtual void add_squares_diagonally(const chessboard &board, vector <int> &allowed_positions, const int position, const int direction, const bool direction_is_top_left_to_down_right) const;
};

#endif /* far_moving_piece_class_h */
