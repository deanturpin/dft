#!/bin/bash

echo '[![Build Status](https://travis-ci.org/deanturpin/dft.svg?branch=master)](https://travis-ci.org/deanturpin/dft)'
echo '[![codecov](https://codecov.io/gh/deanturpin/dft/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/dft)'

TZ=BST-1 date

echo '```cpp'
cat dft.h
echo '```'

# Create a section for each WAV
for svg in wav/*.svg; do

  # Section title and image
  echo "# ${svg%.*}"
  echo "[![]($svg)]($svg)"

  # Print notes if present
  markdown=${svg%%.*}.md
  [[ -e $markdown ]] && cat $markdown

  echo "Listen to the [audio](${svg%.svg})."

done

true
