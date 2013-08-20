#!/bin/bash

for i in {0..19}
do
  `./pa01 ./inputs/input$i` #  > ./test/hello$i
done
