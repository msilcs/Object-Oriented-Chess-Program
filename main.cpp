#include "main.h"
using namespace std;

// friend function to fill chessboard called from its (default) constructor
void fill_chessboard(chessboard &board) {
    // construct a chessboard as it appears at the start of a game
    // by pushing back unique pointers to new "object at square" derived class instances
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new rook(black)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new knight(black)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new bishop(black)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new queen(black)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new king(black)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new bishop(black)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new knight(black)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new rook(black)));
    for (auto position = 8; position < 56; position++) {
        if (position < 16)
            board.board_position_vector.push_back(unique_ptr <object_at_square> (new pawn(black)));
        else if (position > 47 )
            board.board_position_vector.push_back(unique_ptr <object_at_square> (new pawn(white)));
        else {board.board_position_vector.push_back(unique_ptr <object_at_square> (new empty_space));}
    }
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new rook(white)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new knight(white)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new bishop(white)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new queen(white)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new king(white)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new bishop(white)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new knight(white)));
    board.board_position_vector.push_back(unique_ptr <object_at_square> (new rook(white)));
}

// function to promote pawn to a queen, knight, bishop or rook when it reaches the opposite side of the board
void promote_pawn(const int &position, chessboard &input_board) {
    // get the colour of the pawn
    const colour_type pawn_colour = input_board.board_position_vector[position] -> get_colour();
    // output a screen displaying the promotion options
    cout << "\t_________________________________________" << endl;
    cout << "\t| Which type of piece would you like to |" << endl;
    cout << "\t| promote this pawn to?                 |" << endl;
    cout << "\t1_______________________________________1" << endl;
    cout << "\t|    w    |    ^    |   ^^>   |   [_]   |" << endl;
    if (pawn_colour == black) {
        cout << "\t|   /b\\   |   /b\\   |   /b\\   |   /b\\   |" << endl;
    }
    else if (pawn_colour == white) {
        cout << "\t|   /w\\   |   /w\\   |   /w\\   |   /w\\   |" << endl;
    }
    cout << "\t1_________1_________1_________1_________1" << endl;
    cout << "\t|  enter  |  enter  |  enter  |  enter  |" << endl;
    cout << "\t| \"queen\" |\"bishop\" |\"knight\" | \"rook\"  |" << endl;
    cout << "\t1_________1_________1_________1_________1" << endl;
    string promotion_choice;
    bool valid_input_given = false;
    // do the following until valid input is given
    do {
        cout << ">> ";
        // get the user input
        getline(cin, promotion_choice);
        // transform the input to lowercase
        transform(promotion_choice.begin(), promotion_choice.end(), promotion_choice.begin(), ::tolower);
        // take the user's choice of piece and call the swap_pawn template function with the chosen new piece
        if (promotion_choice == "queen") {swap_pawn(queen(pawn_colour), pawn_colour, position, input_board); valid_input_given = true;}
        else if (promotion_choice == "knight") {swap_pawn(knight(pawn_colour), pawn_colour, position, input_board); valid_input_given = true;}
        else if (promotion_choice == "bishop") {swap_pawn(bishop(pawn_colour), pawn_colour, position, input_board); valid_input_given = true;}
        else if (promotion_choice == "rook") {swap_pawn(rook(pawn_colour), pawn_colour, position, input_board); valid_input_given = true;}
        // if the input is not a valid piece name, output a warning message
        else {cout << "\tPlease enter \"queen\", \"bishop\", \"knight\" or \"rook\".\n";}
    } while (!valid_input_given);
}

// template function to swap a pawn for another piece if it is promoted
template <class T>
 void swap_pawn(const T &replacement_piece, const colour_type pawn_colour, const int &position, chessboard &input_board) {
 // ensure this template function is used appropriately
 const int INCOMPATIBLE_TYPE = -9;
 try {
     replacement_piece.get_piece_design();
     // make an extra check to ensure the piece being replaced is a pawn
     if (input_board.board_position_vector[position] -> get_piece_design() != "  o  ") {return;}
     
     // replace the pawn with the chosen new piece
     input_board.board_position_vector[position] = unique_ptr <T> (new T(pawn_colour));
 }
 // catch incompatible types and throw an error
 catch (...) {throw INCOMPATIBLE_TYPE; return;}
 }

// function to move chess piece at random for single player game
void randomly_move_piece(colour_type &computer_side, chessboard &input_board) {
    // seed random number generator with current time
    srand(static_cast <unsigned int> (time(NULL)));
    
    // create an int to store the position of a randomly chosen piece position
    // (unless this side is in check)
    int chosen_piece_position;
    
    // create a boolean variable to ensure that a piece moves
    bool piece_has_moved = false;
    do {
        try {
            // if the computer's king is in check, ensure that it will be the chosen piece
            if (input_board.test_for_check(computer_side)) {chosen_piece_position = input_board.king_positions[computer_side];}
            
            // otherwise, set the chosen piece position to be a random number
            else {chosen_piece_position = rand() % 64;}
            
            // calculate the row and column positions of the chosen piece
            if (computer_side == input_board[chosen_piece_position].get_colour()) {
                int rankNumber = input_board.get_position(chosen_piece_position).first;
                int fileNumber = input_board.get_position(chosen_piece_position).second;
                
                // compute the possible moves available to the chosen piece
                vector <int> possible_moves = input_board[chosen_piece_position].default_moves(rankNumber, fileNumber, input_board);
                
                // check that if it is checkmate the game will end
                if (input_board.test_for_check(computer_side) && possible_moves.size() == 0) {input_board.checkmate = true; break;}
                
                // if a randomly selected piece cannot move, select a new one
                if (possible_moves.size() == 0) {continue;}
                
                // select a random move from the list of available moves for the piece
                const int random_move = rand() % possible_moves.size();
                
                // calculate the new row and column positions and move the piece
                int newRankNumber = input_board.get_position(possible_moves[random_move]).first;
                int newFileNumber = input_board.get_position(possible_moves[random_move]).second;
                input_board.move_piece(rankNumber, fileNumber, newRankNumber, newFileNumber);
                
                // get final position of piece
                int finalPosition = input_board.get_position(newRankNumber, newFileNumber);
                
                // if a pawn reaches the opposite side of the board, it may be promoted
                if (input_board[finalPosition].get_piece_design() == "  o  "
                    && ((finalPosition < 8 && current_turn == black) || (finalPosition > 55 && current_turn == white))) {
                    
                    // generate a random number to select piece type
                    int random_piece_selector = rand() % 4 + 1;
                    
                    // use the random number in a switch statement to swap the pawn for a new piece
                    switch (random_piece_selector) {
                        case 1: {swap_pawn(queen(computer_side), computer_side, finalPosition, input_board); break;}
                        case 2: {swap_pawn(knight(computer_side), computer_side, finalPosition, input_board); break;}
                        case 3: {swap_pawn(bishop(computer_side), computer_side, finalPosition, input_board); break;}
                        case 4: {swap_pawn(rook(computer_side), computer_side, finalPosition, input_board); break;}
                    }
                }
                // state that a piece has moved to break the loop
                piece_has_moved = true;
            }
        }
            catch (int error_flag) {
                if (error_flag == -5) {continue;}
            }
        } while (!piece_has_moved);
    }



void single_player_game(chessboard &input_board) {
    // make colour types to represent the player's side and that of the computer
    colour_type player_side = none;
    colour_type computer_side = none;
    
    // ask the user what side the would like to play as
    cout << "What side do you want to play as? (b/w)" << endl;
    
    // until a suitable colour is chosen
    do {
        cout << ">> ";
        
        // peek at the chosen character and set the side colour_types accordingly
        if (cin.peek() == 'w') {player_side = white; computer_side = black;}
        else if (cin.peek() == 'b') {player_side = black; computer_side = white;}
        
        // else if the input is invalid, print a warning message
        else {cout << "Please enter 'b' for black or 'w' for white." << endl;}
        
        // clear and ignore the cin buffer
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    } while (player_side == none);
    
    // while the input board is not in checkmate
    do {
        // output the board
        cout << input_board;
        
        // on the user's turn
        if (current_turn == player_side) {
            // get user input
            cin >> input_board;
        }
        // on the computer's turn
        else {
            // print newline character and call the function to randomly move a piece
            cout << endl;
            randomly_move_piece(computer_side, input_board);
        }
    } while (!input_board.is_checkmate());
}

// function to play a two player game
void two_player_game(chessboard &input_board) {
    // until the input board is in checkmate
    do {
        // output the input board
        cout << input_board;
        
        // get user input from the current player
        cin >> input_board;
    } while (!input_board.is_checkmate());
    
}

// define the global colour_type for the current turn
colour_type current_turn;

int main() {
    // set the first turn to be the white side
    current_turn = white;
    
    // output the name of the game
    cout << "\n\n\t\t\t\t\t\t CHESS\n\n" << endl;

    // output an ASCII diagram to tell the user to enter 1 or 2 to start a game
    cout << "\t ______________________________________________" << endl;
    cout << "\t | Single Player Game: |   Two Player Game:   |" << endl;
    cout << "\t |       enter '1'     |       enter '2'      |" << endl;
    cout << "\t 1_____________________1______________________1\n" << endl;
    
    cout << ">> ";
    
    // flag to be caught if game is quit
    const int QUIT_FLAG = -9999;
    
    try {
        // make a do/while loop to ensure the input is valid
        do {
            // create a chessboard instance
            chessboard board;
            
            // if a single-player game is chosen
            if (cin.peek() == '1') {
                // clear and ignore the cin buffer
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                // start a single-player game
                single_player_game(board);
            }
            
            // else if a two player game is chosen
            else if (cin.peek() == '2') {
                // clear and ignore the cin buffer
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                // start a two player game
                two_player_game(board);
            }
            
            // if the option to quit is selected, throw the QUIT_FLAG to end the program
            else if (cin.peek() == 'q') {throw QUIT_FLAG;}
            
            // if invalid input is given, print a warning message and restart the loop
            else {cout << "Please enter '1' or '2' to select the number of players. Press 'q' to quit." << endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cout << ">> ";
                continue;
            }
            
            // at the end of a game work out the winner from the last turn played
            string winner (current_turn == 1 ? "White":"Black");
            
            // output the board
            cout << board;
            
            // output the winner and an announcement of checkmate
            cout << endl << "\n\tCHECKMATE\n" << winner << " side wins!\n" << endl;
            
            // output a message to request new input
            cout << "Press '1' or '2' to play again with the chosen number of players.\nPress 'q' to quit." << endl;
            cout << ">> ";
        } while (cin.peek() != 1 || 2);
    }
    // catch an int error
    catch (int error) {
        // if the QUIT_FLAG was thrown, end the program
        if (error == QUIT_FLAG) {return 0;}
    }
    return 0;
}
