echo "enter the string"
read str
length=${#str}
for ((i=length-1;i>=0;i--))
do
  reverse=$reverse${str:$i:1}
done
 if [[ $str == $reverse ]]
   then
   echo "the string $str is a pallindrome"
else
 echo "the string $tsr is not a pallindrome"
 fi     
