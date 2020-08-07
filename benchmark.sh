#!/bin/bash

if [ $# -eq 0 ]
    then
    echo "Usage: ./benchmark.sh [mode] [repeats]"
    echo "	mode - the generator mode from 1 (--flow-one) to 5 (--big-superposition)"
    echo "	repeats - the number of tests"
    exit 1
elif [ "$1" -eq 1 ]
    then
    MODE="--flow-one"
elif [ "$1" -eq 2 ]
    then
    MODE="--flow-ten"
elif [ "$1" -eq 3 ]
    then
    MODE="--flow-thousand"
elif [ "$1" -eq 4 ]
    then
    MODE="--big"
elif [ "$1" -eq 5 ]
    then
    MODE="--big-superposition"
fi

if [ $# -eq 1 ]
    then
    REPEATS=5
    else
    REPEATS="$2"
fi

TIMEFORMAT='%3R'

for (( i=1; i <= $REPEATS; i++ ))
do
		NUMBER_MAP="$(maps/generator $MODE > bench.map && cat bench.map | sed -n '2 p' | tr -dc '0-9')"
        NUMBER_LEMIN="$(./lem-in < bench.map | grep -c '^L')"
		if [ "$NUMBER_MAP" -lt "$NUMBER_LEMIN" ]
			then
            echo -e "$i\tKO: $(($NUMBER_LEMIN - $NUMBER_MAP))\t"
			#cat bench.map >> problems
            echo -n "$(time ./lem-in < bench.map | tail -0)"
            exit 1
		    else
            echo -e "$i\tOK\t"
            echo -n "$(time ./lem-in < bench.map | tail -0)"
		fi
done

rm bench.map