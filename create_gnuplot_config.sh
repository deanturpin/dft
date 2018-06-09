#!/bin/bash

readonly name=$1

# Use a larger font for zoomed plots
[[ $name =~ zoom ]] && font_size=10 || font_size=3

echo set terminal svg size 1500,900
echo set title \"${name//_/ }\"
echo set output \"$name.svg\"
echo set format y \"\"
echo set xtics 10
echo set xtics rotate
echo set xlabel \"Hz\"
echo set grid xtics ytics
echo set tics font \"Helvetica,$font_size\"
echo plot \"$name.csv\" notitle with impulses
echo
