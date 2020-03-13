// Chencheng Xie
// z5237028
// Last Modified: 29/06/2019
// COMP9024 19T2
// Assignment 1: Sliding-Tile Puzzle
// https://wiki.cse.unsw.edu.au/cs9024cgi/19T2/Assignment1

#include <stdio.h>
#include <stdlib.h>
#include "boardADT.h"

int main(void) {
    Board board_1 = initialize();
    if (find_board_error(board_1)) {	//return program if error found
        return EXIT_FAILURE;		//error msg is printed within the check
    }

    Board board_2 = initialize();
    if (find_board_error(board_2)) {
        return EXIT_FAILURE;
    }

    if (compare_size(board_1, board_2)) {//return program if two board are of
        return EXIT_FAILURE;		 //different sizes, error msg is
    }					 //printed within the check

    print_board("\nstart:", board_1);	 //print "start: n1, n2, n3...."
    print_board("goal:", board_2);	 //print "goal: n1, n2, n3...."

    if (compare_parity(board_1, board_2)) {//compare parity of two boards,
        printf("unsolvable\n");		   //print whether boards are solvable,
    } else {				   //and clean up memory used for boards
        printf("solvable\n");
    }
    return EXIT_SUCCESS;		//return program successfully
}					//if no error was found
