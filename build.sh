#!/bin/sh
export LD_LIBRARY_PATH=./lib
qmake -project
qmake Test.pro
./Test
