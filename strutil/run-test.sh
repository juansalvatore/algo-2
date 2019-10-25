#!/bin/bash

echo "Compiling"
gcc -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion -o pruebas *.c 

echo "test"
./pruebas 

echo "valgrind"
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas