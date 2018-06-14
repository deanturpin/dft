#!/bin/bash

cat template.md
TZ=BST-1 date
echo

# Create a section for each WAV
for svg in wav/*.svg; do

  # Prepare SVG file name to convert into other file name
  # stem=${stem/_zoom/}
  # stem=${stem/_full/}

  # # Construct file names
  # wav=wav/$stem.wav
  # title=${stem//_/ }

  # # Print info for the first graph if there is any
  # if [[ $svg =~ full ]]; then

  #   # Print section header
  #   echo "# $title"
  # stem=${file%%.*}
  # echo "Listen to the [audio]($wav)."

  echo "# ${svg%.*}"

  markdown=${svg%%.*}.md
  [[ -e $markdown ]] && cat $markdown

  # Print the SVG
  echo "[![]($svg)]($svg)"
done
