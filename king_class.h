//  king_class.h

#ifndef king_class_h
#define king_class_h

#include "piece_base_class.h"
using namespace std;

// class for king
class king: public piece {
public:
    // constructor
    king(colour_type input_colour): piece(input_colour) {
        piece_design = "  +  ";
    }
    
    // destructor
    ~king() {}
    
    // overridden function to return that this piece is a king to test for check/checkmate
    bool is_king() {return true;}
    
    // function to compute the allowed moves for a king
    vector <int> default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const;
};


#endif /* king_class_h */
