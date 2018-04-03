#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#ifdef __cplusplus
extern "C" {
#endif

int open_port(const char *serial_port);
int set_port(int fd,int iBaudRate,int iDataSize,char cParity,int iStopBit);
int read_port(int fd,void *buf,int iByte);
int write_port(int fd,void *buf,int iByte);
int close_port(int fd);

#ifdef __cplusplus
}
#endif

#endif
