//  colour_type_enum.h

#ifndef colour_type_enum_h
#define colour_type_enum_h

// enum for piece colour
enum colour_type {black, white, none};

// make an external global colour type to keep track of which side has the current turn
extern colour_type current_turn;

#endif /* colour_type_enum_h */
