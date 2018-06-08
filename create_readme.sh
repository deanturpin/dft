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

  # Print section header
  echo "# ${wav#*/}"
  echo "Listen to the [audio]($wav)."
  echo "[![]($svg)]($svg)"
  echo
done
