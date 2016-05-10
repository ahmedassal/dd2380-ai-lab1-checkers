#!/bin/bash
set -x

#g++ *.cpp -std=c++11 -Wall -o checkers
rm debug.log
rm /tmp/mypipe -f
mkfifo /tmp/mypipe

./checkers init verbose < /tmp/mypipe | ./checkers > /tmp/mypipe

