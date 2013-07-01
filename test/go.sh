
# mknod bridge p

ret=0
i=0

# while [ "$ret" == "0" ]
while [ 1 ]
do

    python gen_data.py | tee data| ./ac_1742_2 > result2

    ../musical_theme_1743_suffix_array < data > result1

    diff result1 result2

    ret=$(echo $?)

    i=$(($i+1))

    if [ "$ret" != "0" ]; then
        # echo $i
        mv data data"$i"
    fi

done

# rm bridge
