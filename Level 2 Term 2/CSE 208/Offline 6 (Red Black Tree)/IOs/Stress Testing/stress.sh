for((i=0;i<=10;++i)); do
    echo Test Case $i
    ./a < input$i.txt > outa$i.txt
    ./b < input$i.txt > outb$i.txt
    diff outa$i.txt outb$i.txt && echo "Accepted" || break
done