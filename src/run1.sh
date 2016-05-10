#!/bin/bash
set -x
echo on

g++ *.cpp -std=c++11 -Wall -o checkers
cp checkers playerA
cp checkers playerB
#rm checkers

#cd ../Debug/

rm debug.log
rm /tmp/mypipe -f
mkfifo /tmp/mypipe
./checkers init verbose < /tmp/mypipe | ./checkers > /tmp/mypipe 2> output.log

#chmod 777 checkers playerA playerB
#./visualizer -1 './playerA init' -2 './playerB' -t 800 -r
