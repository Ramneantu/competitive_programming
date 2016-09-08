#!/bin/sh
problem=Routing

echo "compiling generator..."
javac ${problem}Generator.java

#small random inputs
for i in {05..14}
do
	n=10
	ii=`echo $i|sed 's/^0*//'`
	d="0.$((14-ii))"
	name=secret/$i-random-n$n-d$d
	echo "generating file $name..."
	java ${problem}Generator $i $n $d > $name.in
done

#medium random inputs
for i in {15..24}
do
	n=30
	ii=`echo $i|sed 's/^0*//'`
	d="0.$((24-ii))"
	name=secret/$i-random-n$n-d$d
	echo "generating file $name..."
	java ${problem}Generator $i $n $d > $name.in
done

#large random inputs
for i in {25..26}
do
	n=100
	ii=`echo $i|sed 's/^0*//'`
	d="0.$((34-ii))"
	name=secret/$i-random-n$n-d$d
	echo "generating file $name..."
	java ${problem}Generator $i $n $d > $name.in
done


#TODO: add more handcrafted inputs

echo "compiling sample solution..."
solutiondir=../submissions/accepted
javac $solutiondir/$problem.java

#generate outputs
for name in */*.in
do
	echo "solving file ${name%.in}..."
	cat $name | java -cp $solutiondir $problem > ${name%.in}.ans
done
