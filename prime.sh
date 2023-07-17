#generating the prime number of the given range

#!/bin/bash
echo "Enter the lower bound: "
read n1 
echo "Enter the upper bound: "
read n2 
echo "The prime numbers in the given range are "
for((num=$n1;num<=$n2;num++))
do
 is_prime=1
 for((i=2;i<=$num/2;i++))
 do
 if [[ $((num%i)) -eq 0 ]]
 then
 is_prime=0
 break;
 fi
 done

if [[ $is_prime -eq 1 ]]
then
 echo $num
 fi
done

