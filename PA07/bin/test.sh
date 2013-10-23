#!/bin/bash

for i in {0..10}
do
  ./pa07 inputs/input$i\_A inputs/input$i\_B > bin/input$i
  if !(diff bin/input$i expected/expected$i &> /dev/null); then
    echo "Incorrect output (Test Case $i)"
  else
    echo "Correct output (Test Case $i)"
  fi

  valgrind --leak-check=full --tool=memcheck --verbose --log-file=bin/log$i ./pa07 inputs/input$i\_A inputs/input$i\_B &> /dev/null
done

errors=`grep errors bin/log* | awk 'BEGIN { sum = 0 } { sum += $4 } END { print sum }'`

echo "There are $errors memory errors."
