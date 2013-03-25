#!/bin/bash

genedata=help
datafile=data1845
ac=1845
test=sumdiv
i=0

count=0

while [ "$i" == "0" ]
do
    a1=$RANDOM  
    a2=$RANDOM  

    r1=`echo $a1 $a2 | ./$ac`
    # a2=$RANDOM  
    r2=`echo $a1 $a2 | ./$test`

    echo $a1 $a2 $r1  $r2

    if [ "$r1" != "$r2" ]; then
        break;
    fi

    sleep 0.01
done


# ./$genedata > $datafile
# ./$ac < $datafile

# while [ "$i" == "0" ]
# do

    # count=$(( $count + 1 ))
    # echo $count

    # ./$genedata > $datafile

    # cat $datafile

    # l1=`./$ac < $datafile`
    # l2=`./$test < $datafile`

    # echo $l1
    # echo $l2

    # if [ "$l2" != "$l1" ]; then
        # echo $l1
        # echo $l2
        # i=$(( $i + 1 ))
        # cp "$datafile" "$datafile$i"
    # fi

    # sleep 0.01
# done

