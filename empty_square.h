//  empty_square.h

#ifndef empty_square_h
#define empty_square_h

#include "chess_square_interface.h"
using namespace std;

// class for empty piece
class empty_space: public object_at_square {
public:
    // default constructor
    empty_space():object_at_square() {}
    
    // destructor
    ~empty_space() {}
    
    // definition for returning piece design string
    string get_piece_design() const {return piece_design;}
    
    // definition for colour type
    colour_type get_colour() {return none;}

    // override function to return available moves
    vector <int> default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const {
        vector <int> empty_vector;
        return empty_vector;
    }
};
#endif /* empty_square_h */
