#!/bin/sh
MAXBITS=6

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
echo >> my_sim_add_outputs/add$i/out$j.txt
./project3 -simulate add_blifs/add$i.blif add_inputs/add$i/add$j.txt > my_sim_add_outputs/add$i/out$j.txt
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
echo >> my_sim_sub_outputs/sub$i/out$j.txt
./project3 -simulate sub_blifs/sub$i.blif sub_inputs/sub$i/sub$j.txt > my_sim_sub_outputs/sub$i/out$j.txt
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
echo >> my_sim_mult_outputs/mult$i/out$j.txt
./project3 -simulate mult_blifs/mult$i.blif mult_inputs/mult$i/mult$j.txt > my_sim_mult_outputs/mult$i/out$j.txt
done
done
