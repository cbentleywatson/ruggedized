gcc pingnb.c -o pingnb.o -lpthread
TIME=10000000
echo "Welcome to 'test all.sh' i.e. 'tall' Change the ping wait time by changing TIME=<Desired Time> in tall.sh"
echo "tall.sh pings ports /dev/ttyS5 (RS232 Port #1), /dev/ttyS2 (RS232 Port #2), and /dev/ttyS3 (RS485 Port 1) simultaneously"
# I'm not messing around with these permissions
#chmod 777 /dev/ttyS*
sudo ./pingnb.o $TIME /dev/ttyS5  & sudo ./pingnb.o $TIME /dev/ttyS3    & sudo ./pingnb.o $TIME /dev/ttyS2 & sudo ./kill-ping-q.sh 
#sudo ./pingnb.o $TIME /dev/ttyS5  & sudo ./pingnb.o $TIME /dev/ttyS3    & sudo ./pingnb.o $TIME /dev/ttyS2 

#sudo ./kill-ping.sh

#echo "Print out of temp.txt containing received characters:"
#cat temp.txt
#echo "" # blank line



