#!/bin/bash

echo '[![Build Status](https://travis-ci.org/deanturpin/dft.svg?branch=master)](https://travis-ci.org/deanturpin/dft)'
echo '[![codecov](https://codecov.io/gh/deanturpin/dft/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/dft)'

TZ=BST-1 date

echo '```cpp'
cat dft.h
echo '```'

# Create a section for each WAV
for file in wav/*.png; do

  # Section title and image
  title=${file%.*}
  title=$(basename $title)
  title=${title//_/ }
  title=${title^^*}
  echo "# $title"
  echo "[![]($file)]($file)"

  # Print notes if present
  markdown=${file%%.*}.md
  [[ -e $markdown ]] && cat $markdown

  echo "Listen to the [audio](${file%.*}.wav)."

done

true
