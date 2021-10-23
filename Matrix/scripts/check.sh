count=10

make matrix.out

for((i=1;i<=$count;i++))
do
answ=$(./matrix.out < tests/$i.test)
t_answ=$(cat answ/1.answ)
# echo $answ
# echo $t_answ
if [ $t_answ = $answ ]
then
echo "Test $i passed"
else
echo "Test $i not passe: answ = $answ, true answ = $t_answ"
fi
done
