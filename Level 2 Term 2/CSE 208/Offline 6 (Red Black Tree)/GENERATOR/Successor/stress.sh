for((i=0;i<=10;++i)); do
    echo Test Case $i
    ./Successor < input$i.txt > outs$i.txt
    diff outs$i.txt output$i.txt && echo "Accepted" || break
done