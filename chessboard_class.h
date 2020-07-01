//  chessboard_class.h

#ifndef chessboard_class_h
#define chessboard_class_h

#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>
#include <unordered_map>
#include "colour_type_enum.h"
#include "piece_base_class.h"


using namespace std;

// class for the chessboard
class chessboard {
private:
    // vector of unique pointers to object_at_square instances,
    // to store the objects at every board square
    vector<unique_ptr<object_at_square>> board_position_vector;
    
    // boolean flag to indicate whether or not it is checkmate
    bool checkmate = false;
    
    // unordered map to store the current board positions of the kings
    // the keys are the colours of each king
    unordered_map <colour_type, int> king_positions;
    
    // vector of pairs of piece designs and position pairs, to store moves
    vector <pair <string, pair <int, int> > > vector_of_moves_in_game;
    
public:
    // default constructor for chessboard
    chessboard();
    
    // destructor
    ~chessboard();
    
    // function to access checkmate boolean
    bool is_checkmate() {return checkmate;}
    
    // overload "[]" operator to access piece at the corresponding board position
    object_at_square &operator [] (const int &position) const;
    
    // overload "()" operator to return the piece at a given row and column position
    object_at_square &operator() (const int &rowNumber, const int &columnNumber) const;
    
    // function to return position of piece given the rank and file
    int get_position(const int &rowPosition, const int &columnPosition) const;
    
    // function to convert row and column positions into position in vector
    pair <const int, const int> get_position(const int &position) const;
    
    // function to test whether either side is in check
    bool test_for_check(const colour_type &input_colour);
    
    // function to test if a king cannot move to determine if it is checkmate
    bool is_checkmate(const colour_type &input_colour);
    
    // function to promote a pawn to a queen, knight, rook or bishop once it reaches the opposite side of the board
    friend void promote_pawn(const int &position, chessboard &input_board);
    
    // function to print the allowed moves for a piece at a given position on the full board
    void print_available_moves(const int rowPosition, const int columnPosition);
    
    // function to return colour of piece at given position
    colour_type get_colour(const int &position) const;
    
    // function to convert input rank position into column number
    int get_column_position(const char rank) const;
    
    // function to convert input file position into row number
    int get_row_position(const char file) const;
    
    // function to move the chess piece at a given position
    void move_piece(const int initialRowPosition, const int initialColumnPosition, const int finalRowPosition, const int finalColumnPosition);
    
    // function to allow castling
    void castle(const int &rookRowPosition, const int &rookColumnPosition, bool &turn_is_complete);
    
    // function to print a pause menu during a chess game
    void pause_menu() const;
    
    // function to print the information stored on a previously played turn
    void view_turn(const int &turn_number) const;
    
    // function to print a board square in the format of rank followed by file
    void print_square_name(const int &position) const;

    // function to allow input into chessboard from istream
    friend istream &operator >> (istream &is, chessboard &input_board);
    
    // friend function to print board in style of a real chessboard
    friend ostream &operator << (ostream &os, chessboard &input_board);
    
    // friend function to initialise board positions for default constructor
    friend void fill_chessboard(chessboard &board);
    
    // friend function to move a chess piece at random for a single player game
    friend void randomly_move_piece(colour_type &computer_side, chessboard &input_board);
    
    // template function to allow a pawn to be swapped for a new piece type during promotion
    template <class T>
    friend void swap_pawn(const T &replacement_piece, const colour_type pawn_colour, const int &position, chessboard &input_board);
};
#endif /* chessboard_class_h */
