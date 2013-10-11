#!/bin/bash

for i in {1..5}
  do
    valgrind --tool=memcheck --leak-check=full --verbose --log-file=log$i ./pa06 ./images/0$i* ./test$i.ppm >/dev/null

    if [[ $? ]]; then
      echo "succeeded"
    else
      echo "failed"
    fi

    if diff test$i.ppm ./expected/0$i* >/dev/null; then
      echo "Files are the same"
    else
      echo "Failed"
    fi


    grep -q "ERROR SUMMARY: 0 errors from 0 contexts" log$i

    if [[ $? ]]; then
      echo "No errors"
    else
      echo "Errors"
    fi

  done

