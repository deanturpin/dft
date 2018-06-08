#!/bin/bash

cat template.md
TZ=BST-1 date
echo

# Create a section for each WAV
for svg in *.svg; do

  # Reconstruct WAV
  title=${svg%.*}
  wav=wav/$title.wav
  wav=${wav/_zoom/}
  wav=${wav/_full/}
  markdown=${wav%.*}.md

  # Print info for the first graph if there is any
  if [[ $title =~ full ]]; then

    # Print section header
    echo "# ${title//_/ }"

    [[ -e $markdown ]] && cat $markdown
    echo "Listen to the [audio]($wav)."
  fi

  # Print the SVG
  echo "[![]($svg)]($svg)"
done
