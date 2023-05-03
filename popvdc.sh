#dmesg | grep XR17V35X | awk '{print $7 " MMIO on "   "/dev/"$4}' | grep 0xdf100000 | awk '{print $4}'
dmesg | grep XR17V35X | awk '{print $7 " MMIO on "   "/dev/"$4}' 
dmesg | grep XR17V35X | awk '{print $7 " MMIO on "   "/dev/"$4}'>>exar-data.txt 
RS232_1_MMIO=0xdf100000 # This should be the MMIO address of the first RS232 serial chip
RS232_2_MMIO=0xdf100400 #Second serial po
RS485_MMIO=0xdf100800 # First RS485 port. Second probably won't load...

#SERIAL_1=dmesg | grep XR17V35X |  grep $RS232_1_MMIO | awk '{print "/dev/"$4}'
#SERIAL_1=$(dmesg | grep XR17V35X |  grep 0xdf100000 | awk '{print "/dev/"$4}')
SERIAL_1=$(dmesg | grep XR17V35X |  grep $RS232_1_MMIO | awk '{print "/dev/"$4}')
SERIAL_2=$(dmesg | grep XR17V35X |  grep $RS232_2_MMIO | awk '{print "/dev/"$4}')
RS485=$(dmesg | grep XR17V35X |  grep $RS485_MMIO | awk '{print "/dev/"$4}')
#echo $SERIAL_1
#echo $RS485
 # remove exixting links to prevent errors
sudo rm /dev/vdcRS485
sudo rm /dev/vdcRS232
sudo rm /dev/vdcRS232_2


sudo ln $RS485 /dev/vdcRS485
sudo ln $SERIAL_1 /dev/vdcRS232
sudo ln $SERIAL_2 /dev/vdcRS232_2

#char *s7 = "/dev/vdcRS232";
#  char *s8 ="/dev/vdcRS485_2";
#char *s9 = "/dev/vdcRS232_2";


