// Chencheng Xie
// z5237028
// Last Modified: 29/06/2019
// COMP9024 19T2
// Assignment 1: Sliding-Tile Puzzle
// https://wiki.cse.unsw.edu.au/cs9024cgi/19T2/Assignment1

// boardADT.h: an interface definition for a boardADT
typedef struct board *Board;

// Returns new 'Board' type pointer with attributes initialized,
// calls function to read string from stdin and converts the string
// into the set of tile numbers.
// print out error message if number is invalid (e.g. 1->01 prints error msg)
Board initialize(void);

// Takes 'Board' type pointer, prints out error message
// and return EXIT_FAILURE if:
// 1. the line is empty,
// 2. the line contains only 1 number,
// 3. the board is not a size of X by X,
// 4. any number or the blank is missing.
int find_board_error(Board board);

// Takes two 'Board' pointers (board_1 & board_2),
// Returns EXIT_FAILURE if two boards do not have the same size.
int compare_size(Board board_1, Board board_2);

// Prints out tile numbers with specified leading string.
void print_board(char * str, Board board);

// Return EXIT_SUCCESS if two boards have the same calculated parity,
// Cleans up two boards memory and pointer address (to NULL).
int compare_parity(Board board_1, Board board_2);
