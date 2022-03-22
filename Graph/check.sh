count=10

cd build
cmake ..
make
cd ..

for((i=1;i<=$count;i++))
do
answ=$(./build/graph < tests/$i.test)
t_answ=$(cat answ/$i.answ)
# echo $answ
# echo $t_answ
if [[ $t_answ = $answ ]]
then
echo "Test $i passed"
else
echo "Test $i not passed: answ = $answ, true answ = $t_answ"
fi

done
