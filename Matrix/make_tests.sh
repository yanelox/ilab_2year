count_test=10

make gen

for ((i=1;i<=$count_test;i++))
do
./gen > tests/$i.test 
done

