#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdbool.h> 
#include <fcntl.h> 
#include <termios.h> 
#include <stdio.h> 
#include <string.h> 
#include <signal.h> 
#include <pthread.h> 

void sigHandler(int _SIG); 

struct termios tm_Enc; 
int fd_Enc; 
bool loop = true; 
unsigned char c;

int readLine(int fd, char* str)
{
	int n = 0;
	int total = 0;
	do {
		n = read(fd, str, 1);
		total += n;
	} while(n > 0 && *str++ != NULL);
	return total;
}
 
int main(int argc, char** argv) {

    printf("Start With Port : /dev/ttyUSB2\nBaud : 57600bps\n"); 
    memset(&tm_Enc, 0, sizeof(tm_Enc)); 
    tm_Enc.c_iflag = 0; 
    tm_Enc.c_oflag = 0; 
    tm_Enc.c_cflag = CS8 | CREAD | CLOCAL; 
    tm_Enc.c_lflag = 0; 
    tm_Enc.c_cc[VMIN] = 0; 
    tm_Enc.c_cc[VTIME] = 1; 
    fd_Enc = open("/dev/ttyUSB2", O_RDWR); 
    if (fd_Enc < 0) { 
        printf("Error : Cannot open Port\nName\n"); 
        printf("Restart the Program.\n"); 
        return 0; 
    } 
    cfsetospeed(&tm_Enc, B57600); 
    cfsetispeed(&tm_Enc, B57600); 
    tcsetattr(fd_Enc, TCSANOW, &tm_Enc); 
    //init Port End. 
    pthread_t p_thread; 
    int thr_id; 
    int status; 
    signal(SIGINT, sigHandler); 
   
	int ret = 0;
    char buf[256];
    while (loop) { 
	memset(buf, 0x00, sizeof(buf));
	if((ret = readLine(fd_Enc, buf)) < 0)
	{
		printf("read error : %d\n",ret);
		exit(-1);
	}
	if(ret == 0) {
	}
	else
	{
		printf("%s\n",buf);
	}
    } 

    printf("Terminate Program.\n"); 
    return 1; 

} 
void sigHandler(int _SIG) {
    loop = false; 
} 
