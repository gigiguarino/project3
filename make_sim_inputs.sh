#!/bin/sh

g++ -Wall -Werror make_sim_inputs.cpp -o make_inputs

# remove all old outputs
cd add_inputs
rm -rv *
cd ../sub_inputs
rm -rv *
cd ../mult_inputs
rm -rv *
cd ..



# add inputs
for i in {1..15}
do

done

# sub inputs
for i in {1..15}
do
done

# mult inputs
for i in {1..15}
do
done
