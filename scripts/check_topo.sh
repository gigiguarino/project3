#!/bin/sh
cd ..
make clean
make

# add blifs
for i in {1..16}
do
if [[ $(./project3 -topoSort blifs/add_blifs/add$i.blif) ]]
then
echo "FAILED add$i.blif"
fi
done

echo "finished with adds"

# sub blifs
for i in {1..16}
do
if [[ $(./project3 -topoSort blifs/sub_blifs/sub$i.blif) ]]
then
echo "FAILED sub$i.blif"
fi
done

echo "finished with subs"

# mult blifs
for i in {1..16}
do
echo "mult $i ..."
if [[ $(./project3 -topoSort blifs/mult_blifs/mult$i.blif) ]]
then
echo "FAILED mult$i.blif"
fi
done

echo "finished with mults"
echo "done :-)"
