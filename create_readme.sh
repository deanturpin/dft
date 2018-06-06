#!/bin/bash

cat template.md
TZ=BST-1 date

# Create a section for each WAV
for svg in *.svg; do
  wav=wav/${svg%.*}.wav
  echo "# ${wav#*/}"
  echo "Listen to the [audio]($wav)."
  echo "[![]($svg)]($svg)"
done
