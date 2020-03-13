// Chencheng Xie
// z5237028
// Last Modified: 29/06/2019
// COMP9024 19T2
// Assignment 1: Sliding-Tile Puzzle
// https://wiki.cse.unsw.edu.au/cs9024cgi/19T2/Assignment1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "boardADT.h"

struct boardType {
    int count;	// counter for the number of tile scanned (starts at 0)
    int size;	// size of the board (starts at 0)
    int disorder;// total disorder(starts at 0)
    int check;  // set to 0 initially, change to 1 if error was found
				// during stdin string reading
				// "find_board_error" function will be skipped if (check == 1)
    int * ptr; 	// pointer to the tile numbers
};

// Print error msg to desired stream, specific which input is invalid
// (1->1st, 2->2nd, 3->3rd, 4->4th....)
void error_msg_count(FILE *stream, char * str_1, int number, char * str_2) {
    int digit = 1;
    int temp = number;
    while (temp >= 10) {     // calculate how many character that number has
        temp = temp / 10;
        digit++;
    }
    char *order = malloc((digit + 3)*sizeof(char));
    switch ((number) % 10) {
    case 1: sprintf(order, "%dst", number);
            break;
    case 2: sprintf(order, "%dnd", number);
            break;
    case 3: sprintf(order, "%drd", number);
            break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0: sprintf(order, "%dth", number);
            break;
    }
    fprintf(stream,"%s%s%s", str_1, order, str_2); // concatenate all strings
    free(order);
    order = NULL;
    return;
}

// Convert stdin reading strings into tile numbers
int * str_to_numbers(Board board) {
    char *text = malloc(sizeof(char));
    if (text == NULL) {
        fprintf(stderr, "ERROR: Not enough initial memory to store "
			"the 1st input character of this board!\n");
        exit(EXIT_FAILURE);
    }
    int str_count = 0;	    // counter for how many characters are read
    char c;
    while ((c = getchar()) != '\n' && c != EOF){
        *(text+str_count) = c;
        str_count++;
        text = realloc(text,(str_count+1)*sizeof(char));
        if (text == NULL) {
            error_msg_count(stdout, "ERROR: Unable to extend memory to store"
	        	" the ", str_count+1, " input character of this board!\n");
            exit(EXIT_FAILURE);
        }
    }
    *(text+str_count) = '\0';

    int *ptr = malloc(sizeof(int));		// initialze pointer to tile numbers
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: Not enough initial memory for storing "
	    	"the tile numbers of this board!\n");
        exit(EXIT_FAILURE);
    }
    int buffer;		// temporarily store scanned tile number

    // break string into sub-string of each number
    char *pointer = strtok(text, " \t");
    while (pointer != NULL) {
        if (sscanf(pointer,"%d",&buffer) == 1) {
            if (buffer == 0) {  // tile number should be greater than 0,
                                // board->check = 1 if otherwise
                printf("ERROR: '0' is not a valid input!\n");
                board->check = 1;
                free(text);
                text = NULL;
                return NULL;
            }
	    // board->check = 1 if there is leading 0s in any number
            if ((strlen(pointer) - 1) * 10 > buffer) {
                error_msg_count(stdout, "ERROR: The ", board->count+1,
					" input is not a valid tile number!\n");
                board->check = 1;
                free(text);
                text = NULL;
                return NULL;
            }
            ptr = realloc(ptr, (board->count+1)*sizeof(int));
            if (ptr == NULL) {
                error_msg_count(stderr, "ERROR: Fail to extend memory to store"
					" the ", board->count+1, " tile number of this board!\n");
                exit(EXIT_FAILURE);
            }
            *(ptr + board->count) = buffer;	// transfer number in buffer
            (board->count)++;
        } else if (strcmp(pointer,"b") == 0) {	// found 'b'
            ptr = realloc(ptr, (board->count+1)*sizeof(int));
            if (ptr == NULL) {
                error_msg_count(stderr, "ERROR: Fail to extend memory to store"
					" the ", board->count+1, " tile number of this board!\n");
                exit(EXIT_FAILURE);
            }
            *(ptr + board->count) = 0;	   // transfer int 0 instead of buffer
            (board->count)++;
        }
        pointer = strtok(NULL, " \t");
    }
    free(text);
    text = NULL;
    return ptr;
}

// Initialize and return a "Board" type pointer
Board initialize(void) {
    Board board = malloc(sizeof(struct boardType));
    if (board == NULL) {
        fprintf(stderr, "ERROR: Not enough free memory to create "
			"ADT of this board!\n");
        exit(EXIT_FAILURE);
    }
    board->count = 0;
    board->size = 0;
    board->disorder = 0;
    board->check = 0;
    board->ptr = str_to_numbers(board);	// get pointer to the tile numbers
    return board;
}

// Take "Board" type pointer to find if any error in that board
int find_board_error(Board board) {
    if (board->check) {			// error found during "initialize"
        return EXIT_FAILURE;
    }
    if (board->count == 0) {		// empty line
        printf("INVALID INPUT: This is an empty line!\n");
        return EXIT_FAILURE;
    } else if (board->count == 1) {	// line with only 1 number
        printf("INVALID INPUT: The board must be bigger than 2x2!\n");
        return EXIT_FAILURE;
    }

	// board->size is int, power(sqrt(number),2) == number if its square number
    board->size = sqrt(board->count);
    if (pow(board->size,2) != board->count) {
        printf("INVALID INPUT: Numbers in this board can not form "
			"a %dx%d board!\n", board->size + 1, board->size + 1);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < board->count; i++) {
        for (int j = 0; j < board->count; j++) {
            if (i == *(board->ptr + j)) {
                break; //found that number, break out loop to check next number
            } else if (j == board->count - 1) {
                switch (i) {
                case 0:		// check if blank is missing
                    printf("INVALID INPUT: The blank is missing!\n");
                    return EXIT_FAILURE;
					break;
                default:	// check if any number is missing
                    printf("INVALID INPUT: Number '%d' is missing!\n", i);
                    return EXIT_FAILURE;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

// Take two "Board" type pointer, return EXIT_FAILURE if sizes are different
int compare_size(Board board_1, Board board_2) {
    if (board_1->size != board_2->size) { // two boards have different sizes
        printf("INVALID INPUT: Two boards do not have the same size!\n");
        printf("The first board has size: %dx%d\n",
			board_1->size, board_1->size);
        printf("The second board has size: %dx%d\n",
			board_2->size, board_2->size);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// print tile numbers with leading string
void print_board(char * str, Board board) {
    printf("%s",str);
    for (int i = 0; i < board->count; i++) {
        if (*(board->ptr + i) == 0) {
            printf(" b");
        } else {
            printf(" %d", *(board->ptr + i));
        }
    }
    printf("\n");
}

// Take "Board" type pointer, calculate it's disorder
void calculate_disorder(Board board) {
    int blank_row = 0; // the row# of blank(start with 0)
    for (int i = 0; i < board->count; i++) {
        if (*(board->ptr + i) == 0) { // found blank, record it's row#
            blank_row = (i / board->size) + 1;
            continue; // skip to next loop if it's blank
        }
        for (int j = i + 1; j < board->count; j++) {
            if ((*(board->ptr + j) != 0) &&
					(*(board->ptr + i) > *(board->ptr + j))) {
                board->disorder += 1; // calculate total disorder
            }
        }
    }
    if (board->size % 2 == 0) { // add row# if board->size is even
        board->disorder += blank_row;
    }
}

// Take "Board" type pointer, clean up it's space
void clean_board(Board board) { // free all malloced (or realloced) memory
    free(board->ptr);
    board->ptr = NULL;
    free(board);
    board = NULL;
}

// Take two "Board" type pointer, compare their parity and clean up their memory
int compare_parity(Board board_1, Board board_2) {
    calculate_disorder(board_1);	// call function to calculate disorder
    calculate_disorder(board_2);
    if (board_1->disorder % 2 != board_2->disorder % 2) {  // compare parity
        clean_board(board_1);
        clean_board(board_2);
        return EXIT_FAILURE;
    }
    clean_board(board_1);
    clean_board(board_2);
    return EXIT_SUCCESS;
}
