echo "Q1"
echo ""

read count
flag=$count
let flag--
for (( i=0;i< $count ;i++ ))
	do
		for (( j=0;j< $count ;j++ ))
		do
			sum=`expr $i + $j`
			if [ $i == $j ]
			then
				echo -n "*"
			elif [ $sum == $flag ]
			then 
				echo -n "*"
			else
				echo -n " "
			fi
		done
		echo ""
			
	done
	
	
echo ""
echo ""
echo ""

a=2
b=1
val=`expr $count / $a`
val1=`expr $val + $b`
val2=$val1
let val2--
for (( i=0;i<$count;i++ ))
	do
		for (( j=0;j<$count;j++ ))
		do
			sum=`expr $i + $j`
			if [ $i == $j  -a $i -le $val ] 
			then
				echo -n "*"
			elif [ $sum == $flag -a $i -lt $val ] 
			then
				echo -n "*"
				
			elif [ $j == $val -a $i -ge $val1 ]
			then 
				echo -n "*"
			else
				echo -n " "
			fi
		done
		echo ""
			
	done
	

