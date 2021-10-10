count_test=10

for ((i=1;i<=$count_test;i++))
do
t_answ=$(cat answ/$i.answ)
answ=$(./a.out < test/$i.test)
if [ $t_answ = $answ ]
then
echo "Test $i passed"
else
echo "Test $i not passed"
fi
done
