#!/bin/bash

g++ -Wall -O2 implementation.cpp -o output

#*Check if compilation was successful
if [ $? -eq 0 ]; then
#   echo "Compilation successful."
  ./output < poly_test.txt
else
  echo "Compilation failed."
fi

exit 0