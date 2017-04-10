#!/bin/sh
cd sim_inputs
NUMFILES=$(ls -1 | wc -l)
NUMBITS=0
MAXBITS=6
cd ..

# remove my old sim outputs
echo "removing old outputs..."
cd sim_add_outputs
rm -rv *
cd ../sim_sub_outputs
rm -rv *
cd ../sim_mult_outputs
rm -rv *
cd ../my_sim_add_outputs
rm -rv *
cd ../my_sim_sub_outputs
rm -rv *
cd ../my_sim_mult_outputs
rm -rv *
cd ..
echo "done removing outputs"

cd sim

echo "running correct sim for addition..."
# run sim for add inputs
for i in $(seq 1 $NUMFILES)
do
NUMBITS=$(echo "$i / $MAXBITS" | bc)
echo >> ../sim_add_outputs/out$i.txt
./simulator ../add_blifs/add$NUMBITS.blif < ../sim_inputs/sim$i.txt > ../sim_add_outputs/out$i.txt
done

echo "running correct sim for subtraction..."
# run sim for sub inputs
for i in $(seq 1 $NUMFILES)
do
NUMBITS=$(echo "$i / $MAXBITS" | bc)
echo >> ../sim_sub_outputs/out$i.txt
./simulator ../sub_blifs/sub$NUMBITS.blif < ../sim_inputs/sim$i.txt > ../sim_sub_outputs/out$i.txt
done

echo "running correct sim for multiplication..."
# run sim for mult inputs
for i in $(seq 1 $NUMFILES)
do
NUMBITS=$(echo "$i / $MAXBITS" | bc)
echo >> ../sim_mult_outputs/out$i.txt
./simulator ../mult_blifs/mult$NUMBITS.blif < ../sim_inputs/sim$i.txt > ../sim_mult_outputs/out$i.txt
done

cd ..
make clean
make

echo "running my sim for addition..."
# run my sim for add inputs
for i in $(seq 1 $NUMFILES)
do
NUMBITS=$(echo "$i / $MAXBITS" | bc)
echo >> ../my_sim_add_outputs/out$i.txt
./project3 ../add_blifs/add$NUMBITS.blif ../add_inputs/add$i.txt > ../my_sim_add_outputs/out$i.txt
done

echo "running my sim for subtraction..."
# run my sim for sub inputs
for i in $(seq 1 $NUMFILES)
do
NUMBITS=$(echo "$i / $MAXBITS" | bc)
echo >> ../my_sim_sub_outputs/out$i.txt
./project3 ../sub_blifs/sub$NUMBITS.blif ../sub_inputs/sub$i.txt > ../my_sim_sub_outputs/out$i.txt
done

echo "running my sim for multiplication..."
# run my sim for mult inputs
for i in $(seq 1 $NUMFILES)
do
NUMBITS=$(echo "$i / $MAXBITS" | bc)
echo >> ../my_sim_mult_outputs/out$i.txt
./project3 ../mult_blifs/mult$NUMBITS.blif ../mult_inputs/mult$i.txt > ../my_sim_mult_outputs/out$i.txt
done

# make my sim files into files that look like their
# sim outputs
echo "formatting sim outputs..."
g++ -Wall -Werror format_outputs.cpp -o format
for i in $(seq 1 $NUMFILES)
do
./format ../my_sim_add_outputs/out$i.txt > ../my_sim_add_outputs/out$i.txt
./format ../my_sim_sub_outputs/out$i.txt > ../my_sim_sub_outputs/out$i.txt
./format ../my_sim_mult_outputs/out$i.txt > ../my_sim_mult_outputs/out$i.txt
done

echo "\n"

# compare outputs
for i in $(seq 1 $NUMFILES)
do
if [[ $(diff ../my_sim_add_outputs/out$i.txt ../sim_add_outputs/out$i.txt) ]]
then
echo "!!!!!!!! add #$i failed"
else
echo "passed"
fi
if [[ $(diff ../my_sim_sub_outputs/out$i.txt ../sim_sub_outputs/out$i.txt) ]]
then
echo "!!!!!!!! sub #$i failed"
else
echo "passed"
fi
if [[ $(diff ../my_sim_mult_outputs/mult$i.txt ../sim_mult_outputs/out$i.txt) ]]
then
echo "!!!!!!!! mult #$i failed"
else
echo "passed"
fi
done

echo "\n"
echo "done :)"


