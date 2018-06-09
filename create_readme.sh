#!/bin/bash

cat template.md
TZ=BST-1 date
echo

# Create a section for each WAV
for svg in *.svg; do

  # Prepare SVG file name to convert into other file name
  stem=${svg%.*}
  stem=${stem/_zoom/}
  stem=${stem/_full/}

  # Construct file names
  wav=wav/$stem.wav
  markdown=wav/$stem.md
  title=${stem//_/ }

  # Print info for the first graph if there is any
  if [[ $svg =~ full ]]; then

    # Print section header
    echo "# $title"

    [[ -e $markdown ]] && cat $markdown
    echo "Listen to the [audio]($wav)."
  fi

  # Print the SVG
  echo "[![]($svg)]($svg)"
done
