#!/bin/bash


for i in {1..16..1}
	do 
		python3 exp1.py > "./exp1/corpus$i"
done

for i in {1..16..1}
	do 
		python3 exp3.py > "./exp3/corpus$i"
done

for i in {1..16..1}
	do 
		python3 exp4.py > "./exp4/corpus$i"
done