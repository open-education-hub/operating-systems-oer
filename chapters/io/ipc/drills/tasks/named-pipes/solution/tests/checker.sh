#!/bin/bash
# SPDX-License-Identifier: GPL-2.0

FIFO="my-fifo"
EXEC="../src/named_pipe"
INPUT="test_input.txt"
OUTPUT="test_output.txt"

cd ../src || exit
make
cd ../tests || exit
echo

rm -f $FIFO $INPUT $OUTPUT

test_create_fifo() {

    $EXEC > /dev/null 2>&1 &
    sleep 1

    if [[ -p $FIFO ]]; then
        echo "Test for FIFO creation: PASSED"
    else
        echo "Test for FIFO creation: FAILED"
    fi

    pkill -f $EXEC 2>/dev/null
}

test_send_receive() {
    STRING="OS{We make the rullz!!}"
    echo "$STRING" > $INPUT

    $EXEC > $OUTPUT &
    sleep 1

    $EXEC -s < $INPUT
    sleep 1

    if grep -q "$STRING" $OUTPUT; then
        echo "Test for send and receive: PASSED"
    else
        echo "Test for send and receive: FAILED"
    fi

    pkill -f $EXEC 2>/dev/null
    rm -f $INPUT $OUTPUT
}


test_create_fifo
test_send_receive

rm -f $FIFO
