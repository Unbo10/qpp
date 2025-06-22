#!/bin/bash

g++ -Wall -O2 main.cpp SndPoly.cpp SndPolyTerm.cpp Polynomial.cpp PolyTerm.cpp ../src/Rational.cpp ../src/Integer.cpp ../src/Natural.cpp -o output

#*Check if compilation was successful
if [ $? -eq 0 ]; then
#   echo "Compilation successful."
  ./output < poly_test.txt
else
  echo "Compilation failed."
fi

exit 0