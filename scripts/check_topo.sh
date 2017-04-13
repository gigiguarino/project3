#!/bin/sh
cd ..
make clean
make

# add blifs
for i in {1..32}
do
echo "testing add $i..."
./project3 -topoSort blifs/add_blifs/add$i.blif
echo ""
echo ""
done

echo "finished :-)"

