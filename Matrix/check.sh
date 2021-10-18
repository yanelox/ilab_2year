count=10

make matrix

for((i=1;i<=$count;i++))
do
answ=$(./matrix < tests/$i.test)
t_answ=$(cat answ/1.answ)
# echo $answ
# echo $t_answ
if [ $t_answ = $answ ]
then
echo "Test $i passed"
else
echo "Test $i not passed"
fi
done