#!/bin/sh
cd add_inputs
for i in {1..6}
do
cd add$i
NUMFILES=$(ls -1 | wc -l)
for k in $(seq 1 $NUMFILES)
do
NUM=$(echo "$k % 2" | bc)
echo "cin $NUM" >> add$k.txt
done
cd ..
done
