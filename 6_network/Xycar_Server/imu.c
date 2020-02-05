#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <fcntl.h> 
#include <termios.h> 
#include <string.h> 
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

struct termios tm_Enc; 
int fd_IMU; 
unsigned char c;
 
int thr_id; 
int status; 

#define PORT 9003
#define BUF_LEN 1024

pthread_t thread;
pthread_mutex_t mutex;

int serverFd;
int clientFd;

bool mainloop = true;

int readLine(int fd, char* str)
{
	int n = 0;
	int total = 0;
	do {
		n = read(fd, str, 1);
		total += n;
	} while(n > 0 && *str++ != '\n');
	return total;
}
 
int main(int argc, char** argv) 
{
	char buf[BUF_LEN];
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int ret=0, count;
	socklen_t len;


	if(argc != 2)
	{
		fprintf(stderr, "Error [argv : imu tty (/dev/ttyACM1)] \n"); 
		return -1;
	}
	
	    
	/***************** socket ***********************/
	if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("server socket error\n");
		return -1;
	}

	/******************** bind ************************/
	int opt = 1;
	setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if(bind(serverFd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("server bind error\n");
		return -1;
	}

	/******************** listen **********************/
	if(listen(serverFd,1) < 0)
	{
		printf("server listen error\n");
		return -1;
	}
        
	printf("ready\n");
	
	/*************** accept ******************/
	len = sizeof(client_addr);
	clientFd = accept(serverFd, (struct sockaddr*)&client_addr, &len);
	if(clientFd < 0)
	{
		printf("accept fail\n");
		return -1;
	}
	else
	{		
		printf("done\n");		
	}
	sleep(1);
		
    memset(&tm_Enc, 0, sizeof(tm_Enc)); 
    tm_Enc.c_iflag = 0; 
    tm_Enc.c_oflag = 0; 
    tm_Enc.c_cflag = CS8 | CREAD | CLOCAL; 
    tm_Enc.c_lflag = 0; 
    tm_Enc.c_cc[VMIN] = 0; 
    tm_Enc.c_cc[VTIME] = 1; 
    fd_IMU = open(argv[1], O_RDWR); 
    if (fd_IMU < 0) { 
        printf("Error : Cannot open Port %s \n", argv[1]);
        return 0; 
    } 
    cfsetospeed(&tm_Enc, B115200); 
    cfsetispeed(&tm_Enc, B115200); 
    tcsetattr(fd_IMU, TCSANOW, &tm_Enc); 
    
    printf("Start IMU : Baud : 115200bps\n");    
	
    char bufIMU[256];
    while (mainloop) { 
		memset(bufIMU, 0x00, sizeof(bufIMU));
		if((ret = readLine(fd_IMU,  bufIMU)) < 0)
		{
			printf("read error : %d\n",ret);
			exit(-1);
		}
		if(ret == 0) {
		}
		else
		{
			pthread_mutex_lock(&mutex);
			if((write(clientFd, bufIMU, sizeof(bufIMU))) < 0)
			{	
				printf("#client stop\n");
			}
			pthread_mutex_unlock(&mutex);
		} 
	}

    printf("Terminate Program.\n"); 
    return 1; 

} 
