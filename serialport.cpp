#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <strings.h>

#include "serialport.h"

int open_port(const char *serial_port)
{
    int fd = open(serial_port, O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd < 0) {
        perror("Can't Open Serial Port !");
        return -1;
    }

    if(fcntl(fd,F_SETFL,0) < 0) {
        printf("fcntl failed !\n");
        return -1;
    }

    return fd;
}

int set_port(int fd,int iBaudRate,int iDataSize,char cParity,int iStopBit)
{
    int iResult = 0;
    struct termios oldtio,newtio;

    iResult = tcgetattr(fd,&oldtio);/*保存原先串口配置*/
    if(iResult) {
        perror("Can't get old terminal description !");
        return -1;
    }

    bzero(&newtio,sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;/*设置本地连接和接收使用*/

    /*设置输入输出波特率*/
    switch(iBaudRate) {
    case 2400:
        cfsetispeed(&newtio,B2400);
        cfsetospeed(&newtio,B2400);
        break;
    case 4800:
        cfsetispeed(&newtio,B4800);
        cfsetospeed(&newtio,B4800);
        break;
    case 9600:
        cfsetispeed(&newtio,B9600);
        cfsetospeed(&newtio,B9600);
        break;
    case 19200:
        cfsetispeed(&newtio,B19200);
        cfsetospeed(&newtio,B19200);
        break;
    case 38400:
        cfsetispeed(&newtio,B38400);
        cfsetospeed(&newtio,B38400);
        break;
    case 57600:
        cfsetispeed(&newtio,B57600);
        cfsetospeed(&newtio,B57600);
        break;
    case 115200:
        cfsetispeed(&newtio,B115200);
        cfsetospeed(&newtio,B115200);
        break;
    case 460800:
        cfsetispeed(&newtio,B460800);
        cfsetospeed(&newtio,B460800);
        break;
    default:
        printf("Don't exist iBaudRate %d !\n",iBaudRate);
        return -1;
    }

    /*设置数据位*/
    newtio.c_cflag &= (~CSIZE);
    switch(iDataSize) {
    case	7:
        newtio.c_cflag |= CS7;
        break;
    case	8:
        newtio.c_cflag |= CS8;
        break;
    default:
        printf("Don't exist iDataSize %d !\n",iDataSize);
        return -1;
    }

    /*设置校验位*/
    switch(cParity) {
    case 'N':					/*无校验*/
        newtio.c_cflag &= (~PARENB);
        break;
    case 'O':					/*奇校验*/
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':					/*偶校验*/
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= (~PARODD);
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    default:
        printf("Don't exist cParity %c !\n",cParity);
        return -1;
    }

    /*设置停止位*/
    switch(iStopBit) {
    case	1:
        newtio.c_cflag &= (~CSTOPB);
        break;
    case	2:
        newtio.c_cflag |= CSTOPB;
        break;
    default:
        printf("Don't exist iStopBit %d !\n",iStopBit);
        return -1;
    }

    newtio.c_cc[VTIME] = 0;	/*设置等待时间*/
    newtio.c_cc[VMIN] = 0;	/*设置最小字符*/
    tcflush(fd,TCIFLUSH);		/*刷新输入队列(TCIOFLUSH为刷新输入输出队列)*/
    iResult = tcsetattr(fd,TCSANOW,&newtio);	/*激活新的设置使之生效,参数TCSANOW表示更改立即发生*/

    if(iResult) {
        perror("Set new terminal description error !");
        return -1;
    }

    return 0;
}

int read_port(int fd,void *buf,int iByte)
{
    int iLen = 0;
    if(!iByte) {
        printf("Read byte number error !\n");
        return iLen;
    }

    iLen = read(fd,buf,iByte);
    return iLen;
}

int write_port(int fd,void *buf,int iByte)
{
    int iLen = 0;
    if(!iByte) {
        printf("Write byte number error !\n");
        return iLen;
    }

    iLen = write(fd,buf,iByte);
    return iLen;
}

int close_port(int fd)
{
    return close(fd);
}
