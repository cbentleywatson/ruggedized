echo "Beginning glxmany2.sh. Screen Will Freeze for Approximately ten seconds. "

#glxgears > /dev/null &
#sleep .01
counter=1
number=100
if [ $# -eq 0 ]
  then
	  $number=100
    echo "$number gear windows will be allocated"
  else
	  number=$1
fi
while [ $counter -le $number ]
do
glxgears > /dev/null &
sleep .010


#echo $counter
((counter++))
done

echo "Press 'q' to exit"
count=0
while : ; do
read -n 1 k <&1
if [[ $k = q ]] ; then
printf "\nQuitting from the program\n"
break
else
((count=$count+1))
#printf "\nIterate for $count times\n"
echo "Press 'q' to exit"
fi
done

killall glxgears
