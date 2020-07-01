//  piece_base_class.h

#ifndef piece_base_class_h
#define piece_base_class_h

#include "chess_square_interface.h"
#include "chessboard_class.h"
//#include "empty_square.h"
// abstract class to act as base class for chess pieces
class piece: public object_at_square {
public:
    // constructor
    piece(colour_type input_colour): object_at_square() {
        colour = input_colour;
    }
    
    // virtual destructor
    virtual ~piece() {}
    
    // virtual function to return false if piece is not a king
    virtual bool is_king() {return false;}
    
    // virtual function to return the design for the top of a piece
    virtual string get_piece_design() const {return piece_design;}
    
    // virtual function for returning a piece's colour
    virtual colour_type get_colour() {return colour;}
    
    // virtual function to return a piece's basic allowed positions for movement based on its current board position
    virtual vector <int> default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const = 0;
    
    // function to determine whether a piece has moved
    bool &piece_has_moved() {return has_moved;}
};

#endif /* piece_base_class_h */
