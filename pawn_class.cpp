//  pawn_class.cpp

#include "pawn_class.h"

// define the method by which a pawn moves
vector <int> pawn::default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const {
    
    // make a vector of allowed positions
    vector <int> allowed_positions;
    
    // calculate the pawn's current position
    int position = (columnPosition - 1) + ((rowPosition - 1) * 8);
    
    // if the pawn is black, it can move down one square
    if (colour == black && rowPosition != 8) {
        if (board.get_colour(position + 8) == none) {allowed_positions.push_back(position + 8);}
        
        // if the pawn is at its starting position, it may move down two squares if the next square is empty
        if (rowPosition == 2 && board.get_colour(position + 8) == none && board.get_colour(position + 16) == none) {
            allowed_positions.push_back(position + 16);
        }
    }
    
    // if pawn is white, it can move up one square
    else if (colour == white && rowPosition != 1) {
        if (board.get_colour(position - 8) == none) {allowed_positions.push_back(position - 8);}
        
        // if the pawn is at its starting position, it may move up two squares if the next square is empty
        if (rowPosition == 7 && board.get_colour(position - 8) == none && board.get_colour(position - 16) == none) {
            allowed_positions.push_back(position - 16);
        }
    }
    
    // define how a pawn may capture pieces diagonally using if loops
    if (columnPosition != 1 && rowPosition != 8) {
        if (colour == black && board.get_colour(position + 7) == white)
            {allowed_positions.push_back(position + 7);}
    }
    if (columnPosition != 1 && rowPosition != 1) {
        if (colour == white && board.get_colour(position - 9) == black)
            {allowed_positions.push_back(position - 9);}
    }
    if (columnPosition != 8 && rowPosition != 8) {
        if (colour == black && board.get_colour(position + 9) == white)
            {allowed_positions.push_back(position + 9);}
    }
    if (columnPosition != 8 && rowPosition != 1) {
        if (colour == white && board.get_colour(position - 7) == black)
            {allowed_positions.push_back(position - 7);}
    }
    
    // sort and return the vector of allowed moves
    sort(allowed_positions.rbegin(), allowed_positions.rend());
    return allowed_positions;
}
