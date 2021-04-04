#!/bin/bash

declare -a difficulty=("Easy" "Medium" "Hard")
for j in ${difficulty[@]}
do
    echo "Running $j Tests:"
    for i in {1..6..1}
    do
        echo "$j $i:"
        time valgrind ./kevin-21 tests/${j}/test_${i}.txt results/${j}/test_${i}_out.txt
    done
    echo "Finished $j Tests"
done