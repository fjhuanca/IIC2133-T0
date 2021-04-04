#!/bin/bash

declare -a difficulty=("Easy" "Medium" "Hard")
for j in ${difficulty[@]}
do
    echo "Difference $j Tests:"
    for i in {1..6..1}
    do
        echo -n "$j $i:"
        r="$(diff -w solutions/${j}/test_${i}.txt results_python/${j}/test_${i}_out.txt)"
        if [ -z "$r" ]
        then
            echo "Passed - No difference"
        else
            echo "Failed - $r"
        fi

    done
    echo "End $j Tests"
    
done

