
# get the Serial Ports for reference
sudo cat /proc/tty/driver/xrserial
#chmod o+rw /dev/ttyS1
# Set all the XR serial ports to be read and write accessible 
sudo  chmod o+rw /dev/ttyXR*

for VARIABLE in /dev/ttyXR0 /dev/ttyXR1 /dev/ttyXR2 /dev/ttyXR3
do
    echo -ne "\x7E\x03\xD0\xAF und normaler                                                              Text" > $VARIABLE
    echo "Sending to $VARIABLE"

done


sudo  chmod o+rw /dev/ttyS*
sudo cat /proc/tty/driver/serial
for VARIABLE in /dev/ttyS0 /dev/ttyS1 /dev/ttyS2 /dev/ttyS3 /dev/ttyS4 /dev/ttyS5
do
    echo -ne "\x7E\x03\xD0\xAF und normaler                                                              Text" > $VARIABLE
    echo "Sending to $VARIABLE"

done
