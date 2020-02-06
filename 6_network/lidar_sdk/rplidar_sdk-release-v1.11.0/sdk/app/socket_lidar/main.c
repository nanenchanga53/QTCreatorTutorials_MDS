#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>


#define BUF_LEN 1024
#define PORT 9004     

#include "rplidar.h" //RPLIDAR standard sdk, all-in-one header

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#include <unistd.h>
static inline void delay(_word_size_t ms){
	while (ms>=1000){
		usleep(1000*1000);
		ms-=1000;
	}
	if (ms!=0)
		usleep(ms*1000);
}


using namespace rp::standalone::rplidar;

bool checkRPLIDARHealth(RPlidarDriver * drv)
{
	u_result     op_result;
	rplidar_response_device_health_t healthinfo;

	op_result = drv->getHealth(healthinfo);
	if (IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
		printf("RPLidar health status : %d\n", healthinfo.status);

		if (healthinfo.status == RPLIDAR_STATUS_ERROR) {
			fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
			// enable the following code if you want rplidar to be reboot by software
			// drv->reset();
			return false;
		} else {
			return true;
		}
	} else {
		fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
		return false;
	}
}

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int)
{
	ctrl_c_pressed = true;
}

int serverFd;
int clientFd;

int main(int argc, const char * argv[]) {
	const char * opt_com_path = argv[1];
	_u32         opt_com_baudrate = 115200;
	u_result     op_result;

	char buf[BUF_LEN];
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int ret=0;
	int count;
	socklen_t len;

	if(argc != 2)
	{
		fprintf(stderr, "Error [argv : rpLidar tty (/dev/ttyUSB2)] \n"); 
		return -1;
	}		

	printf("Ultra simple LIDAR data grabber for RPLIDAR.\n"
	"Version: "RPLIDAR_SDK_VERSION"\n");
	printf("My RPLIDAR\n");


	// create the driver instance
	RPlidarDriver * drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
	if (!drv) {
		fprintf(stderr, "insufficent memory, exit\n");
		exit(-2);
	}

	rplidar_response_device_info_t devinfo;
	bool connectSuccess = false;
	// make connection...

	if(!drv)
		drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);

	if (IS_OK(drv->connect(opt_com_path, opt_com_baudrate)))
	{
		op_result = drv->getDeviceInfo(devinfo);

		if (IS_OK(op_result)) 
		{
			connectSuccess = true;
		}
		else
		{
			delete drv;
			drv = NULL;
		}
	}

	if (!connectSuccess) {
		fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n", opt_com_path);
		goto on_finished;
	}

	// print out the device serial number, firmware and hardware version number..
	printf("RPLIDAR S/N: ");
	for (int pos = 0; pos < 16 ;++pos) {
		printf("%02X", devinfo.serialnum[pos]);
	}

	printf("\n"
		"Firmware Ver: %d.%02d\n"
		"Hardware Rev: %d\n"
		, devinfo.firmware_version>>8
		, devinfo.firmware_version & 0xFF
		, (int)devinfo.hardware_version);



	// check health...
	if (!checkRPLIDARHealth(drv)) {
		goto on_finished;
	}

	signal(SIGINT, ctrlc);

	    
	/***************** socket ***********************/
	if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("server socket error\n");
		return -1;
	}

	/******************** bind ************************/
	int opt;
	opt = 1;
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
	
	
	drv->startMotor();
	// start scan...
	drv->startScan(0,1);

	// fetech result and print it out...

	int msg_size;
	
	int iDist[360];
	char msg[30000];
	
	while (1) {
		rplidar_response_measurement_node_t nodes[8192];
		size_t   count = _countof(nodes);

		op_result = drv->grabScanData(nodes, count);

		if (IS_OK(op_result)) {
			drv->ascendScanData(nodes, count);
			for (int pos = 0; pos < (int)count ; ++pos) {
				int theta = (int)(nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f;
				int Dist = (int)(nodes[pos].distance_q2/4.0f);

				iDist[theta] = Dist;
				if(theta >= 359)				
				{
					sprintf(msg, "[");
					msg_size = strlen(msg)+1;
					for (int j = 0; j < 360 ; j++) {
						sprintf(msg, "%s|%03ld_%d", msg, j, iDist[j]);
					}
					sprintf(msg, "%s]",msg);
					msg_size = strlen(msg)+1;
					if((write(clientFd, msg, msg_size))<0)
					{
						printf("write error\n");
						drv->stop();
						drv->stopMotor();
						return -1;
					}
					memset(msg, 0x00, sizeof(msg));
				}
				
				printf("%s theta: %03.2f Dist: %08.2f Q: %d - th:%d, dist:%d, len:%d \n", 
					(nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ?"S ":"  ", 
					(nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f,
					nodes[pos].distance_q2/4.0f,
					nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT, theta, Dist, msg_size);
			}
		}

		if (ctrl_c_pressed){ 
			break;
		}
	}

	drv->stop();
	drv->stopMotor();
	// done!
	on_finished:
	RPlidarDriver::DisposeDriver(drv);
	drv = NULL;
	return 0;
}

