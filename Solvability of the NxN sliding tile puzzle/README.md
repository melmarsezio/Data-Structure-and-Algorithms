# Solvability of the NxN sliding tile puzzle
#### Coursework assignment for Data Structure and Algorithms
![puzzle2.png](https://github.com/melmarsezio/Data-Structure-and-Algorithms/blob/master/Solvability%20of%20the%20NxN%20sliding%20tile%20puzzle/puzzle2.png)
## Specification
In regards to problem description, input format, output messages, details are explained in [*`Assignment1.pdf`*](https://github.com/melmarsezio/Data-Structure-and-Algorithms/blob/master/Solvability%20of%20the%20NxN%20sliding%20tile%20puzzle/Assignment1.pdf) and [*`TuteSTPuzzle.pdf`*](https://github.com/melmarsezio/Data-Structure-and-Algorithms/blob/master/Solvability%20of%20the%20NxN%20sliding%20tile%20puzzle/TuteSTPuzzle.pdf)
## Instruction
> cmd run `make` to compile [`puzzle.c`](https://github.com/melmarsezio/Data-Structure-and-Algorithms/blob/master/Solvability%20of%20the%20NxN%20sliding%20tile%20puzzle/puzzle.c) and [`boardADT.c`](https://github.com/melmarsezio/Data-Structure-and-Algorithms/blob/master/Solvability%20of%20the%20NxN%20sliding%20tile%20puzzle/boardADT.c) into `puzzle`
>>  `./puzzle` to execute it or `./puzzle < Tests/[testfile].inp` to test the file with predefined testcases
>
> or
>> cmd run `chmod +x ./test.sh` to give permission to the shellscript, and
>>
>> cmd run `./test.sh [1|2|3|4]` to automatically run sets of testfiles
>

> Sample input:

>       2 11 6 16 23 4 15 24 14 3 13 1 b 5 8 22 9 12 20 10 7 21 19 17 18
>       23 8 17 5 2 3 14 7 10 21 15 6 11 b 22 24 13 1 16 12 20 19 9 4 18

> Expected ouput:

>       start: 2 11 6 16 23 4 15 24 14 3 13 1 b 5 8 22 9 12 20 10 7 21 19 17 18
>       goal: 23 8 17 5 2 3 14 7 10 21 15 6 11 b 22 24 13 1 16 12 20 19 9 4 18
>       solvable

## [`boardADT.c`](https://github.com/melmarsezio/Data-Structure-and-Algorithms/blob/master/Solvability%20of%20the%20NxN%20sliding%20tile%20puzzle/boardADT.c) description
>#### ADT Structure:
>+ `struct boardType`: a `board` data type, it includes:  
&emsp;&emsp;`count` counter for the number of tile scanned  
&emsp;&emsp;`size` size of the board (expect to be `sqrt(count+1)`)  
&emsp;&emsp;`disorder` total disorder of board object  
&emsp;&emsp;`check` the status of whether error is found during `stdin` string scanning  
&emsp;&emsp;`* ptr` pointer to the tile numbers
>
>+ `Board`: pointer to the `boardType`
>#### ADT Functions:
>+ `void error_msg_count(FILE *stream, char * str_1, int number, char * str_2)`: Print memory msg `ERROR: Unable to extend memory to store the {ith} input character of this board!` to desired stream.
>
>+ `int* str_to_numbers(Board board)`: Convert stdin reading strings into tile numbers and store in  
&emsp;&emsp;`board.ptr/Board->ptr`, it calls `error_msg_count()` to generate msg if not enough memory.
>
>+ `Board initialize(void)`: Initialize boardType object and return it's pointer.
>
>+ `int find_board_error(Board board)`: Take `Board` pointer and try to find if any invalid input error in that board (size error, not enough tile number, missing tile number, etc)
>
>+ `int compare_size(Board board_1, Board board_2)`: compare if two `boardType` objects have the same size.
>
>+ `void print_board(char * str, Board board)`: Print tile numbers with leading strings.
>
>+ `void calculate_disorder(Board board)`: Take `Board` type pointer and calculate it's disorder.
>
>+ `void clean_board(Board board)`: `Board` memory warehousing, clean up used memory space.
>
>+ `int compare_parity(Board board_1, Board board_2)`: Compare two `Board`s' parity(`Board->disorder`) and clean up their memory by calling `clean_board`.
## Testfiles
> all testcases are store under `Tests`, `bad[*].inp` represent bad inputs, `sol[*].inp` represent inputs with solutions, `unsol[*].inp` represent inputs without solutions.

