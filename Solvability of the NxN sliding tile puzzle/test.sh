#!/bin/sh
PROG=./puzzle       # running program
DIR=Tests           # directory of testcases

case $1 in
"1") T=$DIR/bad* ;;
"2") T=$DIR/sol* ;;
"3") T=$DIR/unsol* ;;
"4") T=$DIR/* ;;
esac

# if we have valid command
if [ A$T != A ];
then
    # test all selected testfiles
    for i in $T
    do
        echo =================  $i  ================== | tee -a "$DIR/result.log"
        # print result to the terminal, and save it to the log file as well
        result= $PROG < $i | tee -a "$DIR/result.log"
    done

elif [ ! $T];
#  print out error msg
then echo "Usage:\n  $0 [1|2|3|4]\nCommands:\n  1: bad input\n  2: sol input\n  3: unsol input\n  4: all testfiles"

else echo "Usage:\n  $0 [1|2|3|4]\nCommands:\n  1: bad input\n  2: sol input\n  3: unsol input\n  4: all testfiles"
fi
