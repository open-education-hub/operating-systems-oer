#!/bin/bash
# SPDX-License-Identifier: GPL-2.0

TCP="../src/tcp_socket"
UDP="../src/udp_socket"

TCP_LOG="tcp_server.log"
UDP_LOG="udp_server.log"

cd ../src || exit
make
cd ../tests || exit
echo

test_tcp_all() {

    $TCP > "$TCP_LOG" 2>&1 &
    TCP_PID=$!
    sleep 1

    IP="127.0.0.1"
    PORT="5000"

    if netstat -tuln | grep -q "$IP:$PORT"; then
        echo "Test for TCP state: PASSED"
    else
        echo "Test for TCP state: FAILED"
    fi

    STRING="OS{Hello OS enjoyers!!}"
    echo "$STRING" | $TCP -s
    sleep 1

    if grep -q "\[Receiver\]: $STRING" "$TCP_LOG"; then
        echo "Test for TCP receiving the message: PASSED"
    else
        echo "Test for TCP receiving the message: FAILED"
    fi

    kill "$TCP_PID" 2>/dev/null
    wait "$TCP_PID" 2>/dev/null
    rm -f "$TCP_LOG"
    echo
}

test_udp_all() {

    $UDP > "$UDP_LOG" 2>&1 &
    UDP_PID=$!
    sleep 1

    IP="127.0.0.1"
    PORT="5000"

    if netstat -tuln | grep -q "$IP:$PORT"; then
        echo "Test for UDP state: PASSED"
    else
        echo "Test for UDP state: FAILED"
    fi

    STRING="OS{Are you enjoying this lab?!}"
    echo "$STRING" | $UDP -s
    sleep 1

    if grep -q "\[Receiver\]: $STRING" "$UDP_LOG"; then
        echo "Test for UDP receiving the message: PASSED"
    else
        echo "Test for UDP receiving the message: FAILED"
    fi

    kill "$UDP_PID" 2>/dev/null
    wait "$UDP_PID" 2>/dev/null
    rm -f "$UDP_LOG"
    echo
}

test_tcp_all
test_udp_all

rm -f "$INPUT" "$OUTPUT"
