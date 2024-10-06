#!/bin/bash

g++ main.cpp -o exe -I/usr/include/opencv4 `pkg-config --cflags --libs opencv4`
./exe

exit 0
