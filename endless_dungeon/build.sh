#!/bin/sh
eval cc main.c -framework IOKit -framework Cocoa -framework OpenGL $(pkg-config --libs --cflags raylib) -o EndlessDungeon