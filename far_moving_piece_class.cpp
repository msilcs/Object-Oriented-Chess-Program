//  far_moving_piece_class.cpp

#include "far_moving_piece_class.h"
using namespace std;

// implementation for function to find and return available moves for a far-moving piece by calling the square-adding functions
vector <int> far_moving_piece::default_moves(const int &rowPosition, const int &columnPosition, const chessboard &board) const {
    // create vector for allowed moves
    vector <int> allowed_positions;
    
    // calculate the current piece position
    int position = (columnPosition - 1) + ((rowPosition - 1) * 8);
    
    // add moves available in all horizontal and vertical directions to vector
    add_squares_horizontally_or_vertically(board, allowed_positions, position, -1, false);
    add_squares_horizontally_or_vertically(board, allowed_positions, position, 1, false);
    add_squares_horizontally_or_vertically(board, allowed_positions, position, -1, true);
    add_squares_horizontally_or_vertically(board, allowed_positions, position, 1, true);
    
    // add moves available in all diagonal directions around piece to vector
    add_squares_diagonally(board, allowed_positions, position, -1, true);
    add_squares_diagonally(board, allowed_positions, position, 1, true);
    add_squares_diagonally(board, allowed_positions, position, -1, false);
    add_squares_diagonally(board, allowed_positions, position, 1, false);
    
    // sort and return the vector
    sort(allowed_positions.rbegin(), allowed_positions.rend());
    return allowed_positions;
}

// implementation for virtual function to work out available moves in a horizontal or direction for use in possible moves function
void far_moving_piece::add_squares_horizontally_or_vertically(const chessboard &board, vector <int> &allowed_positions, const int position, const int direction, const bool direction_is_vertical) const {
    // get the piece's colour
    colour_type piece_colour = board.get_colour(position);
    
    // if the direction is horizontal
    if (!direction_is_vertical) {
        // if the piece is at the left or right column on the board and the direction is
        // away from the centre of the board, return from the function
        if (((position % 8) + 1 == 1 && direction == -1) || ((position % 8) + 1 == 8 && direction == 1)) {return;}
        
        // make a variable to store the new position
        int newPosition = position + direction;
        
        // do the following while the edge of the board is not reached
        do {
            // if the next piece in the chosen direction is on the same side as the moving piece, break out of loop
            if (board.get_colour(newPosition) == piece_colour) {break;}
            
            // push back the new position otherwise
            allowed_positions.push_back(newPosition);
            
            // if the new position contains an enemy piece, break since the enemy would be captured
            // and the turn would end
            if ((board.get_colour(newPosition) == white && piece_colour == black)
                || (board.get_colour(newPosition) == black && piece_colour == white)) {break;}
            
            // break if the edge of the board is reached
            if ((newPosition % 8) + 1 == 8 || (newPosition % 8) + 1 == 1) {break;}
            
            // update the new position
            newPosition = newPosition + direction;
        } while ((newPosition % 8) + 1 != 0 && (newPosition % 8) + 1 != 9);
    }
    else if (direction_is_vertical) {
        // if the piece is at the top or bottom row on the board and the direction is
        // away from the board centre, return from this function
        if (((position / 8) + 1 == 1 && direction == -1) || ((position / 8) + 1 == 8 && direction == 1)) {return;}
        
        // make a variable to store the new position
        int newPosition = position + direction * 8;
        
        // do the following while the edge of the board is not reached
        do {
            // if the next piece in the chosen direction is on the same side as the moving piece, break out of loop
            if (board.get_colour(newPosition) == piece_colour) {break;}
            
            // push back the new position otherwise
            allowed_positions.push_back(newPosition);
            
            // if the new position contains an enemy piece, break since the enemy would be captured
            // and the turn would end
            if ((board.get_colour(newPosition) == white && piece_colour == black)
                || (board.get_colour(newPosition) == black && piece_colour == white)) {break;}
            
            // break if the edge of the board is reached
            if ((newPosition / 8) + 1 == 1 || (newPosition / 8) + 1 == 8) {break;}
            
            // update the new position
            newPosition = newPosition + direction * 8;
        } while ((newPosition / 8) + 1 != 0 && (newPosition / 8) + 1 != 9);
    }
}

// implementation for virtual function to work out available moves for diagonally moving pieces for use in possible moves function
void far_moving_piece::add_squares_diagonally(const chessboard &board, vector <int> &allowed_positions, const int position, const int direction, const bool direction_is_top_left_to_down_right) const {
    
    // if moving in the chosen direction would immediately leave the board, return from the function
    if (((position / 8) + 1 == 1 && direction == -1) || ((position / 8) + 1 == 8 && direction == 1)) {return;}
    
    // get the piece's colour
    colour_type piece_colour = board.get_colour(position);
    
    // set an int for the change in position to zero
    int change_in_position = 0;
    
    // if the direction is on the top-left to down-right diagonal
    if (direction_is_top_left_to_down_right) {
        // ensure the move is valid
        if (((position % 8) + 1 == 1 && direction == -1) || ((position % 8) + 1 == 8 && direction == 1)) {return;}
        
        // update the change in position
        change_in_position = direction * 9;
    }
    
    // else if the direction is on the top-right to down-left diagonal
    else if (!direction_is_top_left_to_down_right) {
        // ensure the move is valid
        if (((position % 8) + 1 == 1 && direction == 1) || ((position % 8) + 1 == 8 && direction == -1)) {return;}
        
        // update the change in position
        change_in_position = direction * 7;
    }
    
    // set the new position to be the original position plus the computed change
    int newPosition = position + change_in_position;
    
    // do the following until the loop is broken
    do {
        // if the piece at the new position is the same colour as the current piece, break from the loop
        if (board.get_colour(newPosition) == piece_colour) {break;}
        
        // push back the new position
        allowed_positions.push_back(newPosition);
        
        // break if a piece is captured by this move
        if ((board.get_colour(newPosition) == white && piece_colour == black)
            || (board.get_colour(newPosition) == black && piece_colour == white)) {break;}
        
        // break if the board's edge is reached
        if ((newPosition % 8) + 1 == 8 || (newPosition % 8) + 1 == 1
            || (newPosition / 8) + 1 == 1 || (newPosition / 8) + 1 == 8) {break;}
        newPosition = newPosition + change_in_position;
    } while ((newPosition % 8) + 1 != 0 && (newPosition % 8) + 1 != 9 &&
             (newPosition / 8) + 1 != 0 && (newPosition / 8) + 1 != 9);
}
