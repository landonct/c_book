#! /bin/bash

if [[ ! gcc sudoku_solver_v1.c -o main ]]; then
    echo "Complied unoptomized sucessfully..."
fi

if [[ ! gcc -O3 sudoku_solver_v1.c -o main_opt ]]; then
    echo "Complied optimized sucessfully..."
fi

time echo "00015097c6c3 083020090000800100029300008000098700070000060006740000300006980002005000010030540  7.2" | ./main

time echo "00015097c6c3 083020090000800100029300008000098700070000060006740000300006980002005000010030540  7.2" | ./main