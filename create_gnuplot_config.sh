#!/bin/bash

readonly name=$1

echo set terminal svg size 1500,900
echo set output \"$name.svg\"
echo set format y \"\"
echo set xtics 10
echo set xtics rotate
echo set xlabel \"Hz\"
echo set grid xtics ytics
echo set tics font \"Helvetica,10\"
echo plot \"$name.csv\" notitle with impulses
echo
