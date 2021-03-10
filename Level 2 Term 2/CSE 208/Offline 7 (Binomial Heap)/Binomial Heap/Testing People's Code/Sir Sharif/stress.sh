for((i = 0; i<=20; ++i)); do
    echo Test Case $i
    ./gen $i > int.txt
    ./soln < int.txt > out1.txt
    ./nawmi < int.txt > out2.txt
    diff -w out1.txt out2.txt && echo "Accepted" || break
done

# for((i = 0; i<=20; ++i)); do
#     echo Test Case $i
#     ./gen $i > in$i.txt
#     ./soln < in$i.txt > out$i.txt
#     # ./sharif < in$i.txt > outNone.txt
#     # diff -w out1.txt out2.txt && echo "Accepted" || break
# done