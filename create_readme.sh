#!/bin/bash

cat template.md
TZ=BST-1 date
echo

# Create a section for each WAV
for svg in *.svg; do

  # Reconstruct WAV
  wav=wav/${svg%.*}.wav
  wav=${wav/_zoom/}
  wav=${wav/_full/}
  markdown=${wav%.*}.md

  # Print section header
  echo "# ${wav#*/}"

  # Print info if there is any
  [[ -e $markdown ]] && cat $markdown

  # Print the SVG
  echo
  echo "Listen to the [audio]($wav)."
  echo "[![]($svg)]($svg)"
  echo
done
