#!/bin/sh
MAXBITS=6
cd ..
cd outputs
cd my_sim_add_outputs
for i in $(seq 1 $MAXBITS)
do
cd add$i
rm -rvf *
cd ..
done
cd ../my_sim_sub_outputs
for i in $(seq 1 $MAXBITS)
do
cd sub$i
rm -rvf *
cd ..
done
cd ../my_sim_mult_outputs
for i in $(seq 1 $MAXBITS)
do
cd mult$i
rm -rvf *
cd ..
done
cd ..
echo "done removing outputs"

cd ..
make clean
make

echo "running my sim for addition..."
# run my sim for add inputs
for i in $(seq 1 $MAXBITS)
do
NUM=$(echo "(2 ^ (2*$i)) - 1" |bc)
for j in $(seq 0 $NUM)
do
echo "add$i #$j"
echo >> outputs/my_sim_add_outputs/add$i/out$j.txt
./project3 -simulate blifs/add_blifs/add$i.blif inputs/add_inputs/add$i/add$j.txt > outputs/my_sim_add_outputs/add$i/out$j.txt
done
done

echo "running my sim for subtraction..."
# run my sim for sub inputs
for i in $(seq 1 $MAXBITS)
do
NUM=$(echo "(2 ^ (2*$i)) - 1" |bc)
for j in $(seq 0 $NUM)
do
echo "sub$i #$j"
echo >> outputs/my_sim_sub_outputs/sub$i/out$j.txt
./project3 -simulate blifs/sub_blifs/sub$i.blif inputs/sub_inputs/sub$i/sub$j.txt > outputs/my_sim_sub_outputs/sub$i/out$j.txt
done
done

echo "running my sim for multiplication..."
# run my sim for mult inputs
for i in $(seq 1 $MAXBITS)
do
NUM=$(echo "(2 ^ (2*$i)) - 1" |bc)
for j in $(seq 0 $NUM)
do
echo "mult$i #$j"
echo >> outputs/my_sim_mult_outputs/mult$i/out$j.txt
./project3 -simulate blifs/mult_blifs/mult$i.blif inputs/mult_inputs/mult$i/mult$j.txt > outputs/my_sim_mult_outputs/mult$i/out$j.txt
done
done
