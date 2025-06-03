#!/bin/bash

g++ -Wall -O2 implementation_includes.cpp PolyTerm.cpp Polynomial.cpp ../Numbers/ClasesImplementation/Rational.cpp -o output

if [ $? -eq 0 ]; then
  ./output < poly_test.txt
else
  echo "Compilation failed."
fi

exit 0