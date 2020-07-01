//  queen_class.h

#ifndef queen_class_h
#define queen_class_h

#include "far_moving_piece_class.h"

using namespace std;

// class for queen
class queen: public far_moving_piece {
public:
    // constructor
    queen(colour_type input_colour): far_moving_piece(input_colour) {piece_design = "  w  ";}
    
    // destructor
    ~queen() {}
};

#endif /* queen_class_h */
