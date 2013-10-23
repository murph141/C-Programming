#!/bin/bash

for i in {0..10}
do
  `./pa07 inputs/input$i\_A input/input$i\_B > bin/input$i`
  if diff bin/input$i expected/expected$i &> /dev/null; then
    echo "Correct output"
  fi

  `valgrind --leak-check=full --tool=memcheck --verbose --log-file=bin/log$i ./pa07 inputs/input$i\_A inputs/input$i\_B`
done
