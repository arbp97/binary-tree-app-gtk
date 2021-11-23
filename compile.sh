#!/bin/sh

gcc *.c -o test -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic