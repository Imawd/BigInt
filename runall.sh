#! /bin/bash

#To run all test modes at once or decipher all messages at once.
#./runall.sh test
#./runall.sh decipher
#=============================================
#This file is complete, do not change anything!
#=============================================

if [ "$1" = "test" ]; then
	echo "============"
	make clean > /dev/null 2>&1
  output=$(make test 2>&1)
  if [ $? -ne 0 ]; then 
      echo "Compilation Failed!"
      exit 1
  fi
	testcases=9
	bases=(2 10 16)
	for i in "${bases[@]}"
	do
		echo -e "===== base $i tests ===="
		for j in $(seq 0 $testcases)
		do
			#run test cases
			./test $i $j | tail -1
		done
		echo "==== tests for base $i done ===="
	done
  make clean > /dev/null 2>&1
elif [ "$1" = "decipher" ]; then
	echo "============"
	make clean > /dev/null 2>&1
  output=$(make 2>&1)
  if [ $? -ne 0 ]; then 
      echo "Compilation Failed!"
      exit 1
  fi
	echo -e "==== Decipher messages ===="
	messages=8
	for i in $(seq 1 $messages)
	do
		./decipher secret/message$i.txt
	done
	echo "==== decipher done ===="
	make clean > /dev/null 2>&1
else
	echo "Invalid argument!"
  exit 1
fi