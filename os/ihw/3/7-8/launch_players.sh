#!/bin/bash

NUM_PLAYERS=5

echo "Launching $NUM_PLAYERS players..."
for ((i=0; i<NUM_PLAYERS; i++))
do
    ./player > /dev/null 2>&1 &
    echo "Player $i started (PID: $!)"
    PIDS[$i]=$!
done
