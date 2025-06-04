#!/bin/bash

g++ -Wall -O2 implementation_includes.cpp Polynomial.cpp PolyTerm.cpp ../Numbers/Rational.cpp ../Numbers/Integer.cpp -o output

#*Check if compilation was successful
if [ $? -eq 0 ]; then
#   echo "Compilation successful."
  ./output < poly_test.txt
else
  echo "Compilation failed."
fi

exit 0