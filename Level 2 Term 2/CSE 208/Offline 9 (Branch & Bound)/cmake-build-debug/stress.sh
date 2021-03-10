for((i = 0; i<=9; ++i)); do
    echo Test Case $i
    ./branchAndBoundNew < in$i.txt
    # ./bruteRecursive < in$i.txt 
done