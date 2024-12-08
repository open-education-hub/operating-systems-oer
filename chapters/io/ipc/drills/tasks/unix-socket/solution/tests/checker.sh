#!/bin/bash
# SPDX-License-Identifier: GPL-2.0

SOCKET="my-socket"
EXEC="../src/unix_socket"
INPUT="test_input.txt"
OUTPUT="test_output.txt"

cd ../src || exit
make
cd ../tests || exit
echo

rm -f $SOCKET $INPUT $OUTPUT

test_create_socket() {

    $EXEC > /dev/null 2>&1 &
    sleep 1

    if [[ -e $SOCKET ]]; then
        echo "Test for socket creation: PASSED"
    else
        echo "Test for socket creation: FAILED"
    fi

    pkill -f $EXEC 2>/dev/null
}

test_send_receive() {
    STRING="OS{Welcome to the hood!}"
    echo "$STRING" > $INPUT

    $EXEC > $OUTPUT 2>&1 &
    sleep 1

    $EXEC -s < $INPUT > /dev/null 2>&1
    sleep 1

    if grep -q "$STRING" $OUTPUT; then
        echo "Test for send and receive: PASSED"
    else
        echo "Test for send and receive: FAILED"
    fi

    pkill -f $EXEC 2>/dev/null
    rm -f $INPUT $OUTPUT
}

test_create_socket
test_send_receive

rm -f $SOCKET
