for((i = 0; i<=10; ++i)); do
    echo Test Case $i
    ./gen $i > int.txt
    ./soln < int.txt > out1.txt
    ./newtest < int.txt > out2.txt
    diff -w out1.txt out2.txt && echo "Accepted" || break
done