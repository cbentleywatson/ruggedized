#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>




#include <sys/types.h>
#include <fcntl.h>
static int serial_port;
static int t1;
   static FILE *fptr;
void *myThreadFun(void *vargp)
{
	printf("\nThread says hello.\n\n");
   
   	//fptr = fopen("temp3.txt","w");
	int *myid = (int *)vargp;
	char read_buf [256];	
	while(true){	
	//sleep(1);//	if()
	
	// This is part of a transition 
	int bytes;
   	
	if( ioctl(serial_port, FIONREAD, &bytes)<0 ){
	 	printf("ioctl error");
	 }
	 else{
	 //	 printf("Bytes received: %d",bytes);
	 	if(bytes>0){
        		memset(&read_buf, '\0', sizeof(read_buf));	
			int n = read(serial_port, &read_buf, sizeof(read_buf));
   			printf("message from remote: %s \n",read_buf); 
	// Windows sends weird ^M characters at the end of the line, ignore them 
		}

	 }
	}
}
	
	// These 3 lines work!
        //memset(&read_buf, '\0', sizeof(read_buf));	
	//int n = read(serial_port, &read_buf, sizeof(read_buf));
   	//fprintf(fptr,"%s",read_buf, bytes); // Windows sends weird ^M characters at the end of the line, ignore them 
	//int n = read(serial_port, &read_buf, sizeof(read_buf));
	/*   
	if(timer <=0 || 1){
   	//int n = read(serial_port, &read_buf, sizeof(read_buf));
	
   	//printf("thread"); // Windows sends weird ^M characters at the end of the line, ignore them 
}DESCRIPTION         top

       write() writes up to count bytes from the buffer starting at buf
       to the file referred to by the file descriptor fd.

       The number of bytes written may be less than count if, for
       example, there is insufficient space on the underlying physical
       medium, or the RLIMIT_FSIZE resource limit is encountered (see
       setrlimit(2)), or the call was interrupted by a signal handler
       after having written less than count bytes.  (See also pipe(7).)

       For a seekable file (i.e., one to which lseek(2) may be applied,
       for example, a regular file) writing takes place at the file
       offset, and the file offset is incremented by the number of bytes
       actually written.  If the file was open(2)ed with O_APPEND, the
       file offset is first set to the end of the file before writing.
       The adjustment of the file offset and the write operation are
       performed as an atomic step.
	/*
	for(int i =0; i<30; i++){
	sleep(1);
	char read_buf [256];	
   	int n = read(serial_port, &read_buf, sizeof(read_buf));
   	fprintf(fptr,"%s",read_buf); // Windows sends weird ^M characters at the end of the line, ignore them 
	}
	*/


int main(int argc, char *argv[]) {
   // printf() displays the string inside quotation
   int num;
   //FILE *fptr;
   

   //fptr = fopen("temp.txt","w");
   const char * target_device;
 
  if(argc>2){
	// Name of the target device. If a non default device file is going to be used
	// we need to add a time out since the file name is the second option. 
       target_device = argv[2];
  
  }else{
 	// change me back!! 
  	target_device = "/dev/ttyS3";
  }
  
  const char* port_id;
  char * s2 =  "/dev/ttyS2";
  char * s3 ="/dev/ttyS3";
  char *s5 ="/dev/ttyS5";

  if(strcmp(target_device, s3)==0){
  	port_id = "RS485";
  }else if(strcmp(target_device, s2) ==0 ){
  	port_id = "RS232_Port_2";
  } else if(strcmp(target_device,s5)==0){
  	port_id="RS232_Port_1";
  }else{
  	port_id="unknown_port";
  }




      printf("\nTesting %s, Please set your serial console to 9600 baud 8N1 to communicate with this test program\n",target_device);
   //usleep(100000);
   //"/dev/ttyS3";
   char ttyX[] ="ttyS_";
   const char * dev_name = target_device +5;
   char s[] = "ttyS3_temp.txt";
   memcpy(s, target_device+5,5); 
   
   memcpy(ttyX, target_device+5,5);// fill ttyX with actual device name 
  // t1 = open(s, O_RDWR | O_CREAT);
   char end[] ="_temp.txt";
   char fname[50] = "";

   strcat(fname,ttyX);
   strcat(fname,end);   

   const char temptest[50] ="temptest.txt"; 
   fptr = fopen(fname,"w");
   if(fptr == NULL)
   {
      printf("Error opening log file!");   
      exit(1);             
   }


   int serial_port = open(target_device, O_RDWR );
   if (serial_port < 0) {
         printf("Error %i while opening device file: %s\n", errno, strerror(errno));
   	fclose(fptr);
	 exit(1);
   }
	
   struct termios tty;

   if(tcgetattr(serial_port, &tty) != 0) {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
	}
//tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common) 
   
tty.c_cflag |= CRTSCTS;  // Enable RTS/CTS hardware flow control
tty.c_cc[VMIN] = 0; // 1, 0 was working with blocking
   tty.c_cc[VTIME] = 0;
   //tty.c_cflag &= ~CRTSCTS;
   //tty |= TIOCM_RTS;
   int status;


   ioctl(serial_port, TIOCMGET, &status);
   status |= TIOCM_RTS;
   ioctl(serial_port, TIOCMSET, &status); 

   tty.c_lflag &= ~ECHO; // Disable echo
   //tty.c_lflag |= ECHO; // enable echo
   tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); 
   /*  
   tty.c_cflag &= ~PARENB;
   tty.c_cflag &= ~CSTOPB;
   tty.c_cflag |= CS8;
   tty.c_cflag &= ~CRTSCTS;
   tty.c_lflag &= ~ICANON; 
   //https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
   tty.c_lflag &= ~ECHO;

   tty.c_lflag &= ~ECHOE;
   tty.c_lflag &= ~ECHONL;

   tty.c_lflag &= ~ISIG;
   tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl

   tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
 tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
   ty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)

*/

   tcsetattr(serial_port, TCSANOW, &tty);   
   


   unsigned char echo_msg[] = { ' ', '-','-','-','>', ' ', 'M','S', 'G',' ', 'R', 'E', 'C', 'E', 'I', 'V', 'E', 'D', ':', ' '   };
   unsigned char msg[] = {' ', '-','-','-','>', ' ', 'P', 'i', 'n', 'g', '!', '\n'};

   
   int seconds_to_send =10; // default number of seconds to send
   // if we got an argument from the command line, let's override the defualt 
   // value of seconds_to_send
   if(argc>1){
   	seconds_to_send = atoi(argv[1]);
   }
   

   int millisecond_read_wait =10;// 
   int loops_needed = seconds_to_send*1000/millisecond_read_wait;
	
   int write_period = 100;
   int timer = -1;
   //clock_t start_time = clock();

   //static int s = 0;
   //pthread_t tid;
   //pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
   const char gap_str[] = " on ";	

   for(int i =0; i < seconds_to_send; i++ ){
         
	write(serial_port, target_device, strlen(target_device));
	write(serial_port, gap_str, strlen(gap_str));
	write(serial_port, port_id, strlen(port_id));
	write(serial_port, msg, sizeof(msg));
	printf("%s",target_device);
	//printf(" on %s ", port_id);
	printf(" <---  Sent ping to remote.\n");
	int bytes;
	char read_buf[256];
	
	for(int j =0; j<10; j++){
	ioctl(serial_port, FIONREAD, &bytes);	
	
	if(bytes>0){
        		memset(&read_buf, '\0', sizeof(read_buf));	
			int n = read(serial_port, &read_buf, sizeof(read_buf));

   			printf("%s on %s ---> Message from remote: %s  \n", target_device, port_id, read_buf); 
   			//printf("%s  ---> Message from remote: %s  \n", target_device, read_buf); 
			
			write(serial_port,target_device, strlen(target_device));
			write(serial_port,echo_msg, sizeof(echo_msg));
			write(serial_port, read_buf, bytes);
   			fprintf(fptr,"%s",read_buf); // Windows sends weird ^M characters at the end of the line, ignore them 
	// Windows sends weird ^M characters at the end of the line, ignore them 
		}
	usleep(100000); // .1 second
	}

	/*write(serial_port, msg, sizeof(msg));
		timer = write_period;
	}   
   	int n = read(serial_port, &read_buf, sizeof(read_buf));
	timer = timer - millisecond_read_wait;
	//sleep(millisecond_read_wait/10);
    	delay(1);
	*/
   }
    //int cancel_ret_val = pthread_cancel(tid);
   //if (s != 0){ handle_error_en(s, "pthread_cancel"); }

   //write(serial_port, msg, sizeof(msg));
   close(serial_port);


   //printf("Enter num: ");
   //scanf("%d",&num);
   //fprintf(fptr,"%s",msg); // Windows sends weird ^M characters at the end of the line, ignore them 
   fclose(fptr);

   
   return 0;
}

