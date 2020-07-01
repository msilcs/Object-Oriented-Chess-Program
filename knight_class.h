//  knight_class.hpp

#ifndef knight_class_h
#define knight_class_h

#include "piece_base_class.h"
using namespace std;

// class for knight
class knight: public piece {
public:
    // constructor
    knight(colour_type input_colour): piece(input_colour) {
        piece_design = " ^^> ";
    }
    
    // destructor
    ~knight() {}

    // function to determine allowed positions for a knight
    vector <int> default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const;
};

#endif /* knight_class_h */
