#!/bin/sh

g++ -Wall -Werror make_sim_inputs1.cpp -o make_inputs1

mkdir stupid_sub_inputs
NUM=0

for i in {0..7}
do
for j in {0..7}
do
echo >> stupid_sub_inputs/sub$NUM.txt
./make_inputs1 3 $i $j > stupid_sub_inputs/sub$NUM.txt
NUM=$(echo "$NUM + 1" | bc)
done
done

g++ -Wall -Werror twos_comp_3bit.cpp -o twos_comp
NUM=0
for i in {0..7}
do
for j in {0..7}
do
./twos_comp $i
./twos_comp $j
k=$(./twos_comp $i)
l=$(./twos_comp $j)
echo "$k - $l" | bc
./project3 -simulate sub_blifs/sub3.blif stupid_sub_inputs/sub$NUM.txt
echo "\n"
NUM=$(echo "$NUM + 1" | bc)
done
done
