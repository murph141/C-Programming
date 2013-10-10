#!/bin/bash

for i in {1..5}
  do
    `./pa06 ./images/0$i* ./test$i.ppm`
    `diff test$i.ppm ./expected/0$i*`
  done

