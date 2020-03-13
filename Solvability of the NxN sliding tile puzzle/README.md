# Solvability of the NxN sliding tile puzzle
## Coursework assignment for Data Structure and Algorithms
### Specification
In regards to problem description, input format, output messages, details are explained in *`Assignment1.pdf`* and *`TuteSTPuzzle.pdf`*
### Instruction
> cmd run `make` to compile `puzzle.c` and `boardADT.c` into `puzzle`
>>  `./puzzle` to execute the it or `./puzzle < Tests/[testfile].inp` to test the file with predefined testcases, or
> 
>> cmd run `chmod +x ./test.sh` to give permission to the shellscript, and
>>
>> cmd run `./test.sh [1|2|3|4]` to automatically run sets of testfiles

### boardADT description
>+ `struct board`
>
>+ `void error_msg_count(FILE *stream, char * str_1, int number, char * str_2)`:
>
>+ `int* str_to_numbers(Board board)`:
>
>+ `Board initialize(void)`:
>
>+ `int find_board_error(Board board)`:
>
>+ `int compare_size(Board board_1, Board board_2)`:
>
>+ `void print_board(char * str, Board board)`:
>
>+ `void calculate_disorder(Board board)`:
>
>+ `void clean_board(Board board)`:
>
>+ `int compare_parity(Board board_1, Board board_2)`:


