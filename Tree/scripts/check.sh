count_test=10

make tree.out

for ((i=1;i<=$count_test;i++))
do
answ=$(./tree.out < tests/$i.test)
t_answ=$(cat answ/$i.answ)
# echo $answ
# echo $t_answ
if [ "$t_answ" = "$answ" ]
then
echo "Test $i passed"
else
echo "Test $i not passed"
fi
done