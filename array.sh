echo "enter the numbers os elemnts"
read n
echo "Enter the elements"
for((i=0;i<n;i++))
do
 read element
 array+=($element)
done
largest=${array[0]}
for((i=0;i<$n;i++))
do
  if [[ ${array[i]} -gt $largest ]]
  then 
      largest=${array[i]}
  fi    
done 

echo "the largest element in the array is $largest"
