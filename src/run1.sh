#!/bin/bash
set -x
echo on

g++ *.cpp -std=c++11 -Wall -o checkers -w
cp checkers playerA
cp checkers playerB
chmod 777 checkers playerA playerB
rm checkers

#cd ../Debug/

rm debug.log
rm /tmp/mypipe -f
mkfifo /tmp/mypipe

./playerA init verbose < /tmp/mypipe | ./playerB > /tmp/mypipe
#./playerA init verbose < /tmp/mypipe | ./playerB > /tmp/mypipe 2> output.log



#./visualizer -1 './playerA init' -2 './playerB' -t 800 -r
