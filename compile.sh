#!/bin/bash

gcc -ansi -I include -pedantic-errors -Wall -Wextra -g source/knights_tour.c test/knights_tour_test.c -fPIC -lbitarray -L. -Wl,-rpath="\$ORIGIN" -o knights_tour.out

