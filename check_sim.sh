#!/bin/sh
MAXBITS=6

g++ -Wall -Werror check_sim.cpp -o check_sim

for i in $(seq 1 $MAXBITS)
do
NUM=$(echo "2^(2*$i) - 1" |bc)
for j in $(seq 0 $NUM)
do
if [[ $(./check_sim -add $i add_inputs/add$i/add$j.txt my_sim_add_outputs/add$i/out$j.txt) ]]
then
echo "FAILED add$i #$j"
fi
done
done

for i in $(seq 1 $MAXBITS)
do
NUM=$(echo "2^(2*$i) - 1" |bc)
for j in $(seq 0 $NUM)
do
if [[ $(./check_sim -sub $i sub_inputs/sub$i/sub$j.txt my_sim_sub_outputs/sub$i/out$j.txt) ]]
then
echo "FAILED sub$i #$j"
fi
done
done

for i in {1..5}
do
NUM=$(echo "2^(2*$i) - 1" |bc)
for j in $(seq 0 $NUM)
do
if [[ $(./check_sim -mult $i mult_inputs/mult$i/mult$j.txt my_sim_mult_outputs/mult$i/out$j.txt) ]]
then
echo "FAILED mult$i #$j"
fi
done
done

echo "done :-)"
