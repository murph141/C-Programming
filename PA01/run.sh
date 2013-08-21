#!/bin/bash
# bash script to call function multiple times

thepath='./inputs/input'
thepath2='./test/expected'
for i in {0..19}
do
  string=$thepath$i
  string2=$thepath2$i
  `./pa01 $string > $string2`
done
