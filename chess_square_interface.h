//  chess_piece_base_class.h

#ifndef chess_square_interface_h
#define chess_square_interface_h

#include <iostream>
#include <string>
#include <vector>
#include "colour_type_enum.h"

// forward declaration of chessboard class
class chessboard;

using namespace std;

// abstract class to act as interface for the content at a certain square
class object_at_square {
protected:
    string piece_design;
    colour_type colour;
public:
    // default constructor
    object_at_square() {
        piece_design = "     ";
        colour = none;
    }
    
    // virtual destructor
    virtual ~object_at_square() {}
    
    // virtual function to return false if piece is not a king
    virtual bool is_king() {return false;}
    
    // pure virtual function to return the design for the top of a piece
    virtual string get_piece_design() const = 0;
    
    // pure virtual function for returning a piece's colour
    virtual colour_type get_colour() = 0;
    
    // virtual function to determine whether there is a piece at the current square
    virtual bool contains_piece() {return piece_design != "     ";}
    
    // pure virtual function for default moves of the content of a board square
    virtual vector <int> default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const = 0;
    
    // boolean and virtual function to determine whether a piece has moved
    bool has_moved = false;
    virtual bool &piece_has_moved() {return has_moved;}
    
    // friend function to overload output operator
    friend ostream &operator << (ostream &os, object_at_square &board_square);
};

#endif /* chess_piece_base_class_h */
