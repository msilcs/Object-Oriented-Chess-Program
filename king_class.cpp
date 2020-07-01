//  king_class.cpp

#include "king_class.h"
using namespace std;

// implementation for function to return allowed moves for a king
vector <int> king::default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const {
    
    // find the position of the king
    int position = (columnPosition - 1) + ((rowPosition - 1) * 8);
    
    // get and store the colour of the king being considered in a variable
    colour_type colour_of_king = board.get_colour(position);
    
    // make boolean flags to work out which squares will be allowed
    // using the ternary operator to check if the king is at any
    // edge of the board
    bool is_at_left = columnPosition == 1 ? true:false;
    bool is_at_right = columnPosition == 8 ? true:false;
    bool is_at_top = rowPosition == 1 ? true:false;
    bool is_at_bottom = rowPosition == 8 ? true:false;
    
    // create a vector of allowed positions
    vector <int> allowed_positions;
    
    // fill the vector with squares around the king, provided they are not occupied by pieces of the same colour
    // and they do not go over the edge of the board
    if (!is_at_top && board.get_colour(position - 8) != colour_of_king) {allowed_positions.push_back(position - 8);}
    if (!is_at_bottom && board.get_colour(position + 8) != colour_of_king) {allowed_positions.push_back(position + 8);}
    if (!is_at_left && board.get_colour(position - 1) != colour_of_king) {allowed_positions.push_back(position - 1);}
    if (!is_at_right && board.get_colour(position + 1) != colour_of_king) {allowed_positions.push_back(position + 1);}
    if (!is_at_top && !is_at_left && board.get_colour(position - 9) != colour_of_king) {allowed_positions.push_back(position - 9);}
    if (!is_at_top && !is_at_right && board.get_colour(position - 7) != colour_of_king) {allowed_positions.push_back(position - 7);}
    if (!is_at_bottom && !is_at_left && board.get_colour(position + 7) != colour_of_king) {allowed_positions.push_back(position + 7);}
    if (!is_at_bottom && !is_at_right && board.get_colour(position + 9) != colour_of_king) {allowed_positions.push_back(position + 9);}
    
    // sort and return the vector of allowed positions
    sort(allowed_positions.rbegin(), allowed_positions.rend());
    return allowed_positions;
}
