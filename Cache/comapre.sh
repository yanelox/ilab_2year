count_test=10

for ((i=1;i<=$count_test;i++))
do
arc_answ=$(cat ARC/answ/$i.answ)
prf_answ=$(cat perfect_cache/answ/$i.answ)
if [ $arc_answ -gt $prf_answ ]
then
echo "Test $i: ARC"
else
echo "Test $i: perfect_cache"
fi
done
