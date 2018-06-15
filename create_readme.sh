#!/bin/bash

cat template.md
TZ=BST-1 date
echo

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
