#!/bin/bash
g++ -O2 -Wall $@ -o output && ./output || echo "Compilation failed. Please check your code for errors."
