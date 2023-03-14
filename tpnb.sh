gcc pingnb.c -o pingnb.o -lpthread
./pingnb.o 20 
echo "Print out of temp.txt containing received characters:"
cat temp.txt
echo "" # blank line
