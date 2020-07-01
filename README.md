# Object-Oriented Chess Program


The full set of necessary C++ and header files required to run this application is provided in the file "chess_program.zip". These files may be added to a new project in an IDE and run using the main program "main.cpp". Additionally, each of these files is provided in this repository.


Upon starting the program, the user is prompted to enter "1" or "2" to start a single or two player game respectively. "q" may also be pressed to exit the application. For a single player game, the user is then prompted to enter their chosen side ("b" for black and "w" for white). For a two player game, the turns are taken as usual.

In order to take a turn, the start and end positions of the piece to be moved must be entered. For example, to move the knight at square b1 at the start of the game to square c3, the user would enter "b1 c3".

Entering "pause" displays a pause menu. Possible inputs are then "r" to return to the game, "i" to list instructions for the game and "q" to quit the application.

Typing "turn _x_" will display the piece moved and its start and end positions for turn number _x_, providing _x_ is a valid turn number.

To perform a castling manoeuvre, "castle " should be typed followed by the position of the unmoved rook (e.g. "a1") to be used in the castle. This is only possible if the king and rook have not moved and the spaces between them are unoccupied.

If a pawn reaches the opposite side of the board, it is promoted. A template function is called in order to swap the pawn for a new piece of the chosen type. To choose the piece type, the player is prompted to enter either "queen", "bishop", "knight" or "rook". 

Moves are not allowed that would place a player's own king into check. When checkmate occurs at the end of a game, the winning side is displayed and the options to play again or to quit are presented.
