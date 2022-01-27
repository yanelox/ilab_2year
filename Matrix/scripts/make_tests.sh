count_test=10

make gen.out

for ((i=1;i<=$count_test;i++))
do
./gen.out 42 > tests/$i.test 
done

