//  pawn_class.h

#ifndef pawn_class_h
#define pawn_class_h

#include "piece_base_class.h"
using namespace std;

// class for pawn
class pawn: public piece {
public:
    // constructor
    pawn(colour_type input_colour): piece(input_colour) {
        piece_design = "  o  ";
    }
    
    // destructor
    ~pawn() {}
    
    // function to define the method by which a pawn moves
    vector <int> default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const;
};

#endif /* pawn_class_hpp */
