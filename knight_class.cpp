//  knight_class.cpp

#include "knight_class.h"

// implementation for function to determine allowed positions for a knight
vector <int> knight::default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const {
    
    // store the knight's current position
    int position = (columnPosition - 1) + ((rowPosition - 1) * 8);
    
    // get and store the colour of the knight being considered in a variable
    colour_type colour_of_knight = board.get_colour(position);
    
    // make boolean flags to work out which squares will be allowed
    // by checking if the knight is at any edge of the board using
    // the ternary operator
    bool is_at_left = columnPosition == 1 ? true:false;
    bool is_at_right = columnPosition == 8 ? true:false;
    bool is_at_top = rowPosition == 1 ? true:false;
    bool is_at_bottom = rowPosition == 8 ? true:false;
    
    // make a vector to store the knight's allowed moves
    std::vector <int> allowed_positions;
    
    // if the knight is not at an edge of the board, push back the positions allowed for a knight in "L" shaped paths around it:
    
    // if it is not at the left of the board, push back the possible positions
    if (!is_at_left && rowPosition <= 6 && board.get_colour(position + 15) != colour_of_knight) {allowed_positions.push_back(position + 15);}
    if (!is_at_left && rowPosition >= 3 && board.get_colour(position - 17) != colour_of_knight) {allowed_positions.push_back(position - 17);}
    
    // if it is not at the right of the board, push back the possible positions
    if (!is_at_right && rowPosition >= 3 && board.get_colour(position - 15) != colour_of_knight) {allowed_positions.push_back(position - 15);}
    if (!is_at_right && rowPosition <= 6 && board.get_colour(position + 17) != colour_of_knight) {allowed_positions.push_back(position + 17);}
    
    // if it is not at the top of the board, push back the possible positions
    if (!is_at_top && columnPosition >= 3 && board.get_colour(position - 10) != colour_of_knight) {allowed_positions.push_back(position - 10);}
    if (!is_at_top && columnPosition <= 6 && board.get_colour(position - 6) != colour_of_knight) {allowed_positions.push_back(position - 6);}
    
    // if it is not at the bottom of the board, push back the possible positions
    if (!is_at_bottom && columnPosition >= 3 && board.get_colour(position + 6) != colour_of_knight) {allowed_positions.push_back(position + 6);}
    if (!is_at_bottom && columnPosition <= 6 && board.get_colour(position + 10) != colour_of_knight) {allowed_positions.push_back(position + 10);}
    
    // sort and return the vector of allowed moves
    sort(allowed_positions.rbegin(), allowed_positions.rend());
    return allowed_positions;
}
