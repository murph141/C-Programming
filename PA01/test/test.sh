#!/bin/bash

for i in {0..19}
do
  if diff "./expected$i" "../expected/expected$i"; then
    echo "File $i similar"
  else
    echo "File $i differ"
  fi
done
