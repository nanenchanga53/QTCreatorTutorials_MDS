#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

#define PORT 9000
#define BUF_LEN 1024

/* 전역변수로 쓰레드10개(클라이언트10개) 선언 */
pthread_t thread[10];
/* 10개의 클라이언트의 fd번호를 담을 수 있는 배열 선언 */
int cli_fd_arr[10]={0,};

/* thread 구현 , parameter는 클라이언트 fd가 저장되어있는 배열의 index */
void *thread_main(void *num)
{
    int i = *(int *)num;
    int k;
    char buf[BUF_LEN];
    int ret;
    while(1)
    {
        if((ret = read(cli_fd_arr[i], buf, 1024)) < 0)
        {
            printf("read error : %d\n",ret);
            exit(-1);
        }
        else
        {
            /* 클라이언트가 접속 종료시, 클라이언트 fd배열 초기화와 쓰레드 종료 */
            if(ret == 0)
            {
                cli_fd_arr[i] = 0;
                pthread_exit((void *) 0);
            }
            else
            {
                for(k=0; k<10; k++)
                {
                    /* 클라이언트 fd가 0이아닌(접속 중인 클라이언트 fd) 배열에게 write */
                    if(cli_fd_arr[k] != 0)
                    {
                        if((write(cli_fd_arr[k], buf, ret)) < 0)
                        {
                            printf("write error\n");
                            exit(-1);
                        }
						else
						{
                            printf("sended\n");
						}
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    char buf[BUF_LEN];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int ret=0, count;
    socklen_t len;
    int serv_fd;
    int cli_fd;
    int num,x;

    /***************** socket ***********************/
    if((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("server socket error\n");
        return -1;
    }

    /******************** bind ************************/
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if(bind(serv_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("server bind error\n");
        return -1;
    }

    /******************** listen **********************/
    if(listen(serv_fd,10) < 0)
    {
        printf("sercer listen error\n");
        return -1;
    }

    while(1)
    {
        /*************** accept ******************/
        len = sizeof(client_addr);
        cli_fd = accept(serv_fd, (struct sockaddr*)&client_addr, &len);
        if(cli_fd < 0)
        {
            printf("accept fail\n");
            return -1;
        }
        else
        {
            for(x=0; x<10; x++)
            {
                /* accept 성공시, 클라이언트 fd가 할당 안된 배열의 index에 클라이언트 할당 */
                if(cli_fd_arr[x] == 0)
                {
                    cli_fd_arr[x] = cli_fd;
                    /* 할당된 index 번호를 쓰레드에 넘겨줌 */
                    pthread_create(&thread[x], NULL, &thread_main, &x);
                    break;
                }
            }
        }
    }
}