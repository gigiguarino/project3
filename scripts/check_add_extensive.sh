#!/bin/sh
MAXBITS=6

cd ..
cd cpp_make_files

g++ -Wall -Werror check_sim.cpp -o check_sim


for i in $(seq 1 $MAXBITS)
do
NUM=$(echo "2^(2*$i) - 1" |bc)
for j in $(seq 0 $NUM)
do
echo "testing add $i $j"
if [[ $(./check_sim -add $i ../inputs/add_inputs/add$i/add$j.txt ../outputs/my_sim_add_outputs/add$i/out$j.txt) ]]
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
echo "testing sub $i $j"
if [[ $(./check_sim -sub $i ../inputs/sub_inputs/sub$i/sub$j.txt ../outputs/my_sim_sub_outputs/sub$i/out$j.txt) ]]
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
echo "testing mult $i $j"
if [[ $(./check_sim -mult $i ../inputs/mult_inputs/mult$i/mult$j.txt ../outputs/my_sim_mult_outputs/mult$i/out$j.txt) ]]
then
echo "FAILED mult$i #$j"
fi
done
done

echo "done :-)"
