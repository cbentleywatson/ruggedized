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
static int serial_port;
static int t1;
   static FILE *fptr;
void *myThreadFun(void *vargp)
{
	//printf("\nThread says hello.\n\n");
   
   	//fptr = fopen("temp3.txt","w");
	int *myid = (int *)vargp;
while(true){	
	sleep(2);//	if()
	//char read_buf [256];	
   	//int n = read(serial_port, &read_buf, sizeof(read_buf));
	
   	//printf("thread"); // Windows sends weird ^M characters at the end of the line, ignore them 
}
	/*
	for(int i =0; i<30; i++){
	sleep(1);
	char read_buf [256];	
   	int n = read(serial_port, &read_buf, sizeof(read_buf));
   	fprintf(fptr,"%s",read_buf); // Windows sends weird ^M characters at the end of the line, ignore them 
	}
	*/
	unsigned char msg[] = { 't', 'h', 'r', 'e', '!', '\n'};
}


int main() {
   // printf() displays the string inside quotation
   int num;
   //FILE *fptr;
   printf("\nHello, please set your serial console to 9600 baud 8N1 to communicate with this test program\n\n");
   

   //fptr = fopen("temp.txt","w");
   fptr = fopen("temp.txt","w");
   if(fptr == NULL)
   {
      printf("Error opening log file!");   
      exit(1);             
   }
   t1 = open("temp1.txt", O_RDWR);
   int serial_port = open("/dev/ttyS3", O_RDWR);
   if (serial_port < 0) {
         printf("Error %i while opening device file: %s\n", errno, strerror(errno));
   	fclose(fptr);
	 exit(1);
   }
	
   struct termios tty;

   if(tcgetattr(serial_port, &tty) != 0) {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
	}
 
   tty.c_cc[VMIN] = 0; // 1, 0 was working with blocking
   tty.c_cc[VTIME] = 0;
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
   



   unsigned char msg[] = { 'P', 'i', 'n', 'g', '!', '\n'};

   
   int seconds_to_send =10;
   int millisecond_read_wait =10;// 
   int loops_needed = seconds_to_send*1000/millisecond_read_wait;
	
   int write_period = 100;
   int timer = -1;
   //clock_t start_time = clock();

   //static int s = 0;
   pthread_t tid;
   pthread_create(&tid, NULL, myThreadFun, (void *)&tid);


   for(int i =0; i < seconds_to_send; i++ ){
   
	write(serial_port, msg, sizeof(msg));
	printf("%d Sent ping to remote.\n", i);
	sleep(1);
	char read_buf [256];	
   	
	// These 3 lines work!
	//int n = read(serial_port, &read_buf, sizeof(read_buf));
   	//fprintf(fptr,"%s",read_buf); // Windows sends weird ^M characters at the end of the line, ignore them 
   	//printf("message from remote: %s \n",read_buf); // Windows sends weird ^M characters at the end of the line, ignore them 
	//int n = read(serial_port, &read_buf, sizeof(read_buf));
	/*   
	if(timer <=0 || 1){
	write(serial_port, msg, sizeof(msg));
		timer = write_period;
	}   
   	int n = read(serial_port, &read_buf, sizeof(read_buf));
	timer = timer - millisecond_read_wait;
	//sleep(millisecond_read_wait/10);
    	delay(1);
	*/
   }
   printf("sender timed out");
    int cancel_ret_val = pthread_cancel(tid);
   //if (s != 0){ handle_error_en(s, "pthread_cancel"); }

   //write(serial_port, msg, sizeof(msg));
   close(serial_port);


   //printf("Enter num: ");
   //scanf("%d",&num);
   //fprintf(fptr,"%s",msg); // Windows sends weird ^M characters at the end of the line, ignore them 
   fclose(fptr);

   
   return 0;
}

