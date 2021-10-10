count_test=10

for ((i=1;i<=$count_test;i++))
do
./a.out < test/$i.test > answ/$i.answ 
done

