#!/bin/bash

echo "=============build c code============================="
gcc -g src/InverseKinemarics.c -o build/InverseKinematics -lm

./build/InverseKinemarics

# echo "==============conversion=============================="

# python3 launch/header_1.py

# echo "==================Done================================"