//  chessboard_class.cpp

#include "chessboard_class.h"

#include "empty_square.h"

// construct chessboard by default as it appears at the start of a game
chessboard::chessboard() {
    // fill the chessboard vector with instances of classes derived from the object-at-square base class
    fill_chessboard(*this);
    
    // initialise the king position map with the current king positions
    king_positions[black] = 4;
    king_positions[white] = 60;
}

// destructor
chessboard::~chessboard() {}

// overload "[]" operator to access piece at the corresponding board position
object_at_square &chessboard::operator [] (const int &position) const {
    return *board_position_vector[position];
}

// overload "()" operator to return the piece at a given row and column position
object_at_square &chessboard::operator() (const int &rowNumber, const int &columnNumber) const {
    return *board_position_vector[get_position(rowNumber, columnNumber)];
}

// implementation for function to return position of piece given the rank and file
int chessboard::get_position(const int &rowPosition, const int &columnPosition) const {
    return (columnPosition - 1) + ((rowPosition - 1) * 8);
}


// function to return the colour of a piece at a given position
colour_type chessboard::get_colour(const int &position) const {
    colour_type output_colour = board_position_vector[position] -> get_colour();
    return output_colour;
}

// function to print the allowed moves for a piece at a given position on the full board
void chessboard::print_available_moves(const int rowPosition, const int columnPosition) {
    // calculate the integer position in the board position vector from the row and column positions
    int position = this -> get_position(rowPosition, columnPosition);
    
    // if the given square is empty, print a message and return from the function
    if (!board_position_vector[position] -> contains_piece()) {cout << "This is an empty square!" << endl; return;}
    
    // find the default moves available to this piece
    vector <int> moves_vector = board_position_vector[position] -> default_moves(rowPosition, columnPosition, *this);
    
    // output the piece using the overloaded "<<" operator for object_at_square instances
    cout << *board_position_vector[position] << endl;
    
    cout << "Available moves:";
    
    // make boolean to determine whether there are any avilable moves
    bool piece_can_move = false;
    // iterate through the vector of available moves
    for (auto moves_iterator = moves_vector.begin(); moves_iterator != moves_vector.end(); moves_iterator++) {
        cout << " | ";

        // print the squares the piece can move to
        print_square_name(*moves_iterator);
        
        // state that the piece can move
        piece_can_move = true;
    }
    if (piece_can_move) {cout << " |" << endl;}
    
    // if the piece cannot move, tell the user there are no moves available to it
    else {cout << " None." << endl;}
}


// chessboard friend function to output board using ASCII art to resemble a real chessboard
ostream &operator << (ostream &os, chessboard &input_board) {
    
    // create a static int to count the total number of turns
    static int numberOfTurn = 1;
    
    // reset the number of turns when a game ends with checkmate
    if (input_board.is_checkmate()) {numberOfTurn = 1;}
    
    // output top of board with file letters above the relevant squares
    os << "      a     b     c     d     e     f     g     h"  << endl;
    os << "   _________________________________________________\n";
    
    // for every row
    for (auto rowNumber = 0; rowNumber < 8; rowNumber++) {
        os << "   ";
        // for every column
        
        for (auto columnNumber = 0; columnNumber < 8; columnNumber++) {
            // print out the tops of each piece design separated by "|" characters
            
            os << "|" << (input_board.board_position_vector[columnNumber + (rowNumber * 8)]) -> get_piece_design();
        }
        
        // end the current line and output the number of the row in reverse order
        os << "|\n" << (8 - rowNumber) << "  ";
        
        // print out the lower halves of each piece separated by "|" characters
        for (auto columnNumber = 0; columnNumber < 8; columnNumber++) {
            // find the colour of the piece at the current square and print the corresponding piece base
            if (input_board.board_position_vector[columnNumber + (rowNumber * 8)] -> get_colour() == black)
                os << "| /b\\ ";
            else if (input_board.board_position_vector[columnNumber + (rowNumber * 8)] -> get_colour() == white)
                os << "| /w\\ ";
            
            // if the square is currently empty, print white spaces up until the next "|" character
            else
                os << "|     ";
        }
        // output the number of the current row in reverse order and end the current line
        os << "|" << "  " << (8 - rowNumber) << endl;
        
        // output the bottom of each square
        os << "   l_____l_____l_____l_____l_____l_____l_____l_____l" << endl;
    }
    // output the bottom of the board
    os << "      a     b     c     d     e     f     g     h" << endl;
    
    // if the board is in check, print a message telling the user
    if (input_board.test_for_check(current_turn)) cout << "\n\tCHECK!\n" << endl;
    
    // if checkmate has not been reached, print the turn number using the static numberOfTurn variable
    if (!input_board.is_checkmate()) {
        os << endl << "Turn [" << numberOfTurn << "]: ";
        
        // increase the counter for the number of turns
        numberOfTurn++;
    }
    return os;
}

// function definition for printing a pause menu for a chessboard
void chessboard::pause_menu() const {
    // output the menu design
    cout << "\t                   GAME PAUSED                    " << endl;
    cout << "\t__________________________________________________" << endl;
    cout << "\t|        What would you like to do next?         |" << endl;
    cout << "\t1________________________________________________1" << endl;
    cout << "\t|   Resume:  |  View instructions:  |    Quit:   |" << endl;
    cout << "\t|  enter 'r' |       enter 'i'      |  enter 'q' |" << endl;
    cout << "\t1____________1______________________1____________1" << endl;
    
    // make a string to store user input option
    string option;
    
    // make a boolean to determine whether to resume the game
    bool resume_game = false;
    
    // do the following while the game is not resumed
    do {
        // output a prompt and get the line entered by the user
        cout << ">> ";
        getline(cin, option);
        
        // convert the option string to lowercase
        transform(option.begin(), option.end(), option.begin(), ::tolower);
        
        // remove whitespaces and commas from string
        option.erase(remove_if(option.begin(), option.end(),
                               // lambda function to return true if a character is a space or comma
                               [] (const char c) { if (isspace(c) || c == ',') return true; else return false;}), option.end());
        
        // resume the game if 'r' is chosen
        if (option == "r") {cout << "Game resumed!\n>> "; resume_game = true;}
        
        // print instructions for play if 'i' is chosen
        else if (option == "i") {
            cout << "\t INSTRUCTIONS:\n" << endl;
            cout << "To move a piece on your turn, enter the square the piece is currently at,\n" <<
                    "followed by the square you would like it to move to. \n" <<
                    "e.g. to move a piece from square b1 to square c3, enter \"b1, c3\" or \"b1 c3\"." << endl;
            cout << "\nTo view the available moves for a piece, enter \"view\" followed by\n" <<
                    "the square the piece is at." << endl;
            cout << "\nTo view a previous turn in the game, enter \"turn\"\n" <<
                    "followed by the number of the turn you wish to see. " << endl;
            cout << "\nTo castle (if your chosen rook and king have not moved and\n" <<
                    "there are no pieces between them), enter \"castle\" followed by the\n" <<
                    "position of the rook you wish to castle the king with." << endl;
            cout << "\nPress \"r\" now to resume." << endl;
            cout << "\nEnjoy the game!" << endl;
        }
        
        // exit the program if 'q' is chosen by throwing the correct error flag value
        else if (option == "q") {throw -9999;}
        
        // if invalid input is given, print an error message
        else {cout << "\tPlease enter 'r', 'i' or 'q'.\n";}
    } while (!resume_game);
}

// implementation for function to print the information stored on a previously played turn
void chessboard::view_turn(const int &turn_number) const {
    // use ternary operator and the fact that the white side moves first
    // to determine the piece colour
    colour_type piece_colour = (turn_number % 2 == 0? white : black);
    
    // compute the total current number of turns, casting to an int for comparison below
    int number_of_turns = static_cast <int> (vector_of_moves_in_game.size() - 1);
    
    // make sure a valid input is given for the turn number
    if (turn_number < 0 || turn_number > number_of_turns) {throw (-7);}
    
    // special output in the case of castling
    if (vector_of_moves_in_game[turn_number].first == "castle") {
        cout << "A castle was made in turn [" << turn_number + 1 << "]. The rook movement was:" << endl;
        cout << " [_] " << endl;
    }
    
    // default output
    else {
        cout << "\nPiece moved during turn [" << turn_number + 1 << "]:" << endl;
        
        // print the design string for the piece
        cout << vector_of_moves_in_game[turn_number].first << endl;
    }
    
    // print the base of the piece
    cout << (piece_colour == white? " /w\\" : " /b\\");
    
    // print the move made
    cout << "\n\nMove made: ";
    
    // for each square in the move, work out the correct output for the square name
    print_square_name(vector_of_moves_in_game[turn_number].second.first);
    cout << " to ";
    print_square_name(vector_of_moves_in_game[turn_number].second.second);
    cout << ".\n>> ";
}

// function to print a board square in the format of rank followed by file
void chessboard::print_square_name(const int &position) const {
    // get the row and column positions
    int rowNumber = get_position(position).first;
    int columnNumber = get_position(position).second;
    
    // use a switch statement to determine and output the letter corresponding to the file number
    switch(columnNumber) {
        case 1: cout << "a"; break;
        case 2: cout << "b"; break;
        case 3: cout << "c"; break;
        case 4: cout << "d"; break;
        case 5: cout << "e"; break;
        case 6: cout << "f"; break;
        case 7: cout << "g"; break;
        case 8: cout << "h"; break;
    }
    
    // print the rank number after the file letter
    cout << 9 - rowNumber;
}

istream &operator >> (istream &is, chessboard &input_board) {
    // make ints to store the initial and final row and column positions entered by the user
    int initialRowPosition, initialColumnPosition, finalRowPosition, finalColumnPosition;
    
    // make boolean to state whether this turn is complete
    bool turn_is_complete = false;
    
    // test if the current side's king has been checkmated
    if (input_board.test_for_check(current_turn)) {input_board.is_checkmate(current_turn);}
    
    // do the following while the turn is not complete
    do {
        // store the user input line in a string
        string inputString;
        getline(is, inputString);
        
        try {
            // remove whitespaces and commas from the input string
            inputString.erase(remove_if(inputString.begin(), inputString.end(),
                                        // lambda function to return true if a character is a space or comma
                                        [] (const char c) { if (isspace(c) || c == ',') return true;
                                        else return false;
                                        }), inputString.end());
            
            // convert the input string to lowercase
            transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
            
            // if the user enters "view" followed by a board square, the piece at that
            // square and its allowed moves are shown
            if (inputString.substr(0,4) == "view") {
                initialColumnPosition = input_board.get_column_position(inputString[4]);
                initialRowPosition = input_board.get_row_position(inputString[5]);
                input_board.print_available_moves(initialRowPosition, initialColumnPosition);
                cout << "\n>> ";
            }
            
            // if the user enters "castle" followed by a board square corresponding to one of their
            // unmoved rooks, the function for castling is called
            else if (inputString.substr(0,6) == "castle") {
                initialColumnPosition = input_board.get_column_position(inputString[6]);
                initialRowPosition = input_board.get_row_position(inputString[7]);
                input_board.castle(initialRowPosition, initialColumnPosition, turn_is_complete);
            }
            
            // if the user enters "pause", a pause menu is displayed
            else if (inputString.substr(0,5) == "pause") {
                input_board.pause_menu();
            }
            
            // if the user wishes to see a previously played turn
            else if (inputString.substr(0,4) == "turn") {
                // get the turn number from the input string
                int turn_number = stoi(inputString.substr(4));
                
                // call the view_turn function, subtracting one from the turn number
                // since c++ vectors start with element zero
                input_board.view_turn(turn_number - 1);
            }
            else {
                // calculate row and column numbers from input string
                initialColumnPosition = input_board.get_column_position(inputString[0]);
                initialRowPosition = input_board.get_row_position(inputString[1]);
                
                // calculate row and column numbers from input string
                finalColumnPosition = input_board.get_column_position(inputString[2]);
                finalRowPosition = input_board.get_row_position(inputString[3]);
                
                if ((input_board(initialRowPosition, initialColumnPosition)).get_colour() == current_turn) {
                    // if the side is in check, ensure the piece selected to move is the king
                    if (input_board.test_for_check(current_turn) &&
                        !input_board(initialRowPosition, initialColumnPosition).is_king()) {throw -4;}
                    
                    // move the piece
                    input_board.move_piece(initialRowPosition, initialColumnPosition, finalRowPosition, finalColumnPosition);
                    
                    // set the final position
                    int finalPosition = input_board.get_position(finalRowPosition, finalColumnPosition);
                    
                    // if a pawn reaches the opposite side of the board, it may be promoted
                    if (input_board(finalRowPosition, finalColumnPosition).get_piece_design() == "  o  "
                        && ((finalPosition < 8 && current_turn == black) || (finalPosition > 55 && current_turn == white))) {
                        
                        // call the function to promote the pawn
                        promote_pawn(finalPosition, input_board);
                    }
                    turn_is_complete = true;
                }
                else throw (-1);
            }
        }
        // catch thrown values
        catch (int error_flag) {
            // print appropriate responses for each error flag thrown
            if (error_flag == -1) {cout << "This piece is not on your side!\n>> "; continue;}
            if (error_flag == -2) {cout << "This is an illegal move!" << endl;}
            if (error_flag == -3) {cout << "This is not a valid input! Please try again.\n>> ";}
            if (error_flag == -4) {cout << "You are in check! You can only move your king.\n>> ";}
            if (error_flag == -5) {cout << "Moving here puts your king in check! Please try another move.\n>> ";}
            if (error_flag == -6) {cout << "This castle is not possible!\n>> ";}
            if (error_flag == -7) {cout << "This is not a valid turn!\n>> ";}
            
            // throw the QUIT_GAME error flag to the main function to end the game
            if (error_flag == -9999) {throw -9999;}
        }
        // catch anything else which may go wrong
        catch (...) {cout << "Invalid input! Please try again.\n>> ";}
    } while (!turn_is_complete);
    return is;
}

// implementation for function to return the row and column positions of a piece as a pair of integers
pair <const int, const int> chessboard::get_position(const int &position) const {
    // calculate the row and column numbers
     const int rankNumber = ((position)/8) + 1;
     const int fileNumber = ((position)%8) + 1;
    
    // return a pair of these numbers
     return make_pair(rankNumber, fileNumber);
}


// implementation for function to move a chess piece
void chessboard::move_piece(const int initialRowPosition, const int initialColumnPosition, const int finalRowPosition, const int finalColumnPosition) {
    // calculate the index of the initial piece in the board position vector
    const int initialPosition = (initialColumnPosition - 1) + ((initialRowPosition - 1) * 8);
    
    // if there is no piece at this square, do nothing and exit the function
    if (board_position_vector[initialPosition] -> contains_piece() == false) {return;}
    
    // use the relevant overridden function to calculate the positions in the vector
    // that this piece may move to
    vector <int> allowed_positions = board_position_vector[initialPosition] ->
    default_moves(initialRowPosition, initialColumnPosition, *this);
    
    // calculate the index of the desired final position for the piece
    const int finalPosition = (finalColumnPosition - 1) + ((finalRowPosition - 1) * 8);
    
    // check that the current piece may move to the desired new position
    if (count(allowed_positions.begin(), allowed_positions.end(), finalPosition)) {
        // if the move is valid and the opponent's king is captured, set the board's checkmate variable to true
        if (board_position_vector[finalPosition] -> is_king() == true) {
            checkmate = true;//throw "CHECKMATE";
        }
        
        // make temporary unique pointer to store the object at the position being moved to
        unique_ptr <object_at_square> object_at_final_position = move(board_position_vector[finalPosition]);
        
        // move the piece from the initial to the final positions
        board_position_vector[finalPosition] = move(board_position_vector[initialPosition]);
        
        // put a unique pointer to a new empty space in the square the moving piece originally occupied
        board_position_vector[initialPosition] = unique_ptr <object_at_square> (new empty_space);
        
        // if the piece moving is a king, update the position of the king stored in the unordered map of
        // king positions
        if (board_position_vector[finalPosition] -> is_king()) {king_positions[current_turn] = finalPosition;}
            
        // ensure this move has not put the king in check
        if (test_for_check(current_turn)) {
            
            // if the king is now in check, undo the move
            board_position_vector[initialPosition] = move(board_position_vector[finalPosition]);
            board_position_vector[finalPosition] = move(object_at_final_position);
            
            // reset the mapped position of the king if necessary
            if (board_position_vector[initialPosition] -> is_king()) {king_positions[current_turn] = initialPosition;}
            // throw the error corresponding to a move that would put the king in check
            throw (-5);
        }
        
        // make a pair of design string and position pair to store move information
        pair <string, pair <int,int>> move_information;
        
        // store the design of the moving piece
        move_information.first = board_position_vector[finalPosition] -> get_piece_design();
        
        // make a pair of move positions corresponding to the initial and final positions of the moved piece
        pair <int, int> move_positions;
        move_positions.first = initialPosition;
        move_positions.second = finalPosition;
        
        // add the move positions to the move information
        move_information.second = move_positions;
        
        // push the move information back onto the vector of moves
        vector_of_moves_in_game.push_back(move_information);
        
        // work out the colour of the opposing side with ternary operator
        colour_type opposing_side = (current_turn == white? black : white);
        
        // check if the opposing side has been forced into checkmate
        if (test_for_check(opposing_side)) {
            if (is_checkmate(opposing_side)) {return;}
        }
    }
    
    // if the piece cannot make the requested move, throw the illegal move flag
    else {throw (-2);}
    
    // state that the piece has moved
    board_position_vector[finalPosition] -> piece_has_moved() = true;
    
    // return from the function if the board is in a state of checkmate
    if (checkmate) {return;}
    
    // use the ternary operator to switch the current turn between sides as necessary
    else {current_turn == white ? current_turn = black : current_turn = white;}
}

// function to allow castling
void chessboard::castle(const int &rookRowPosition, const int &rookColumnPosition, bool &turn_is_complete) {
    // ensure that the king is not in check and throw an error if it is
    if (test_for_check(current_turn)) {throw (-5);}
    
    // get board position
    const int rookPosition = get_position(rookRowPosition, rookColumnPosition);
    
    // ensure that the piece at the given square is a rook of the correct colour
    if (board_position_vector[rookPosition] ->  get_piece_design() == " [_] "
        && board_position_vector[rookPosition] -> get_colour() == current_turn) {
        
        // ensure that neither the king or rook have moved so far in the game
        if (board_position_vector[king_positions[current_turn]] -> piece_has_moved() == true ||
            board_position_vector[rookPosition] -> piece_has_moved() == true) {throw (-6);}

        // ensure that the squares between the king and rook are empty
        if (
            (rookPosition == 0 && (board_position_vector[1] -> contains_piece() || board_position_vector[2] -> contains_piece() || board_position_vector[3] -> contains_piece() ))
            || (rookPosition == 7 && (board_position_vector[5] -> contains_piece() || board_position_vector[6] -> contains_piece() ))
            || (rookPosition == 56 && (board_position_vector[57] -> contains_piece() || board_position_vector[58] -> contains_piece() ||
                board_position_vector[59] -> contains_piece() ))
            || (rookPosition == 63 && (board_position_vector[61] -> contains_piece() || board_position_vector[62] -> contains_piece() ))
            ) {throw (-6);}
        
        // make an int to temporarily store the new king and rook positions
        int newKingPosition = king_positions[current_turn];
        int newRookPosition = rookPosition;
        
        // if the rook is on the left of the board
        if (rookColumnPosition == 1) {
            // store the new king and rook positions
            newKingPosition = king_positions[current_turn] - 2;
            newRookPosition = rookPosition + 3;
            
            // move the king two spaces left
            board_position_vector[newKingPosition] = move(board_position_vector[king_positions[current_turn]]);
            
            // move the rook three spaces right
            board_position_vector[newRookPosition] = move(board_position_vector[rookPosition]);
            
            // update the rook so it returns true if whether it has moved is checked
            board_position_vector[newRookPosition] -> piece_has_moved() = true;
        }
        
        // else if the rook is on the right of the board
        else if (rookColumnPosition == 8) {
            // store the new king and rook positions
            newKingPosition = king_positions[current_turn] + 2;
            newRookPosition = rookPosition - 2;
            
            // move the king two spaces right
            board_position_vector[newKingPosition] = move(board_position_vector[king_positions[current_turn]]);
            
            // move the rook two spaces left
            board_position_vector[newRookPosition] = move(board_position_vector[rookPosition]);
            
            // update the rook so it returns true if it is checked whether it has moved
            board_position_vector[newRookPosition] -> piece_has_moved() = true;
        }
        
        // replace the original elements of the board position array with unique pointers to new empty spaces
        board_position_vector[king_positions[current_turn]] = unique_ptr <object_at_square> (new empty_space);
        board_position_vector[rookPosition] = unique_ptr <object_at_square> (new empty_space);
        
        // update the king position in the unordered map and state that has moved
        king_positions[current_turn] = newKingPosition;
        board_position_vector[newKingPosition] -> piece_has_moved() = true;
        
        // add the castle to the vector of moves
        pair <string, pair <int, int>> castle_information;
        
        // state that the move was a castle
        castle_information.first = "castle";
        
        // make a temporary pair to store the move made
        pair <int,int> castle_moves;
        castle_moves.first = rookPosition;
        castle_moves.second = newRookPosition;
        
        // set the second element of the castle_information pair to be this temporary pair
        castle_information.second = castle_moves;
        
        // push the castle information back onto the vector of moves
        vector_of_moves_in_game.push_back(castle_information);
        
        // complete the turn
        turn_is_complete = true;
        
        // change the current turn using ternary operator
        current_turn == white ? current_turn = black : current_turn = white;
    }
    else {throw (-6);}
    
}

// implementation for function to test whether either side is in check
bool chessboard::test_for_check(const colour_type &input_colour) {
    // determine the colour of the side opposing
    // the one the function is testing the state of check for
    colour_type opposing_side;
    input_colour == white? opposing_side = black : opposing_side = white;
    
    // iterate through all pieces and find the ones which could put the king in check
    for (auto current_piece_position = 0; current_piece_position != 64;
         current_piece_position++) {
        // if a piece is of the opposing colour, see if
        // one of its moves corresponds to the king's position
        if (board_position_vector[current_piece_position] -> get_colour() == opposing_side) {
            
            // find the current piece's row and column positions
            pair <int, int> current_piece_row_and_column = get_position(current_piece_position);
            
            // find the current piece's available moves
            vector <int> current_piece_moves = board_position_vector[current_piece_position]
            -> default_moves(current_piece_row_and_column.first, current_piece_row_and_column.second, *this);
            
            // if one of these moves could capture the king, return true
            if (count(current_piece_moves.begin(), current_piece_moves.end(), king_positions[input_colour])) {
                return true;
            }
        }
    }
    return false;
}

// function to test if a king cannot move to determine if it is checkmate
bool chessboard::is_checkmate(const colour_type &input_colour) {
    // make boolean assuming the king cannot move
    bool king_can_move = false;
    
    // store the current position of the king in a temporary variable
    const int original_king_position = king_positions[input_colour];
    
    // get the king's column and row positions
    pair <int, int> king_row_and_column = get_position(original_king_position);
    
    // find the king's available moves
    vector <int> king_moves = board_position_vector[king_positions[input_colour]]
    -> default_moves(king_row_and_column.first, king_row_and_column.second, *this);
    
    // for each of these moves, see if the king would be put in check
    for (auto king_moves_it = king_moves.begin(); king_moves_it != king_moves.end(); king_moves_it++) {
        king_positions[input_colour] = *king_moves_it;
        if (!test_for_check(input_colour)) {king_can_move = true;}
    }
    // if the king is in check and cannot move, it is checkmate
    if (king_can_move == false) {checkmate = true;}
    // return the king position stored in the map to its original value
    king_positions[input_colour] = original_king_position;
    return checkmate;
}

// implementation for function to convert input column character into column number
int chessboard::get_column_position(const char rank) const {
    int columnPosition = 0;
    // use switch statement to calculate column position
    switch (rank) {
        case 'a': columnPosition = 1; break;
        case 'b': columnPosition = 2; break;
        case 'c': columnPosition = 3; break;
        case 'd': columnPosition = 4; break;
        case 'e': columnPosition = 5; break;
        case 'f': columnPosition = 6; break;
        case 'g': columnPosition = 7; break;
        case 'h': columnPosition = 8; break;
        // throw an error if the input is invalid
        default: throw (-3);
    };
    return columnPosition;
}

// implementation for function to convert input row character into row number
int chessboard::get_row_position(const char file) const {
    int rowPosition = 0;
    switch (file) {
        // use switch statement to calculate row position
        case '1': rowPosition = 8; break;
        case '2': rowPosition = 7; break;
        case '3': rowPosition = 6; break;
        case '4': rowPosition = 5; break;
        case '5': rowPosition = 4; break;
        case '6': rowPosition = 3; break;
        case '7': rowPosition = 2; break;
        case '8': rowPosition = 1; break;
        // throw an error if the input is invalid
        default: throw (-3);
    };
    return rowPosition;
}
