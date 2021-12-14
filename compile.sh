#!/bin/sh

# compile resources from xml to code
glib-compile-resources --target=src/layout.c --generate-source resource.xml

# compile program
gcc src/*.c -o btree-view -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
