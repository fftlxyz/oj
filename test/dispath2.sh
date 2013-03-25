#!/bin/bash

for ((i=0 ; i <= 50000000; i=i+1 ))
do
    for ((j =1; j <= 2; j=j+1 ))
    do
        r1=`echo $i $j | ./1845`
        r2=`echo $i $j | ./sumdiv`

        # echo $i $j $r1 $r2

        if [ "$r1" != "$r2" ]; then
            echo $i $j $r1 $r2
            # break;
        fi
    done
done
