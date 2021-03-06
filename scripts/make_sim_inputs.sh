#!/bin/sh
cd ..
cd cpp_make_inputs
g++ -Wall -Werror make_sim_inputs1.cpp -o make_inputs1
g++ -Wall -Werror make_sim_inputs2.cpp -o make_inputs2

MAXBITS=6

# remove all old outputs
echo "removing..."
cd ../inputs/add_inputs
for i in $(seq 1 $MAXBITS)
do
cd add$i
rm -rvf *
cd ..
done
cd ../sub_inputs
for i in $(seq 1 $MAXBITS)
do
cd sub$i
rm -rvf *
cd ..
done
cd ../mult_inputs
for i in $(seq 1 $MAXBITS)
do
cd mult$i
rm -rvf *
cd ..
done
cd ../sim_inputs
for i in $(seq 1 $MAXBITS)
do
cd sim$i
rm -rvf *
cd ..
done
cd ..
echo "done removing old files"
echo "\n"

# make inputs
# add, sub and mult are all the same
cd cpp_make_files

for i in $(seq 1 $MAXBITS)
do
MAX=$(echo "(2 ^ $i) - 1" |bc)
NUM=0
for j in $(seq 0 $MAX)
do
for k in $(seq 0 $MAX)
do
echo "making inputs for $j and $k with $i num bits"
./make_inputs1 $i $j $k > ../inputs/add_inputs/add$i/add$NUM.txt
cp ../inputs/add_inputs/add$i/add$NUM.txt ../inputs/sub_inputs/sub$i/sub$NUM.txt
cp ../inputs/sub_inputs/sub$i/sub$NUM.txt ../inputs/mult_inputs/mult$i/mult$NUM.txt
./make_inputs2 $i $j $k > ../inputs/sim_inputs/sim$i/sim$NUM.txt
NUM=$(echo "$NUM + 1" |bc)
done
done
done

