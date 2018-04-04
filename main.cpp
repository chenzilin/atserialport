#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "serialport.h"

#define MAX_SEND_LEN 32
#define MAX_RECEIVE_LEN 128
#define SERIALPORT_TIMEOUT 1000 // 1000ms

int main(int argc, char *argv[])
{
    int fd = -1;
    int iLen = 0;
    int szLen = 0;
    char szChar = 0;
    char szBuffer[MAX_SEND_LEN];

    static struct timespec start_time;
    static struct timespec stop_time;

    if (argc != 3) {
        fprintf(stderr, "Usage: atserialport /dev/ttyUSB2 AT\n");
        return -1;
    }

    if (access(argv[1], F_OK) != 0) {
        return -1;
    }

    fd = open_port(argv[1]);
    if (fd < 0) {
        fprintf(stderr, "Error: open_port error!\n");
        return -1;
    }

    if (set_port(fd, 115200, 8, 'N', 1) < 0) {
        fprintf(stderr, "Error: set_port error!\n");
        return -1;
    }

    strcpy(szBuffer,argv[2]);
    strcat(szBuffer, "\r\n");
    write_port(fd,szBuffer,strlen(szBuffer));

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    while (szLen <= MAX_RECEIVE_LEN) {
        iLen = read_port(fd, &szChar,1);
        if(iLen > 0) {
            szLen += iLen;
            printf("%c", szChar);
        }

        clock_gettime(CLOCK_MONOTONIC, &stop_time);
        if ((stop_time.tv_sec - start_time.tv_sec)*1000
                + (stop_time.tv_nsec - start_time.tv_nsec)/1000000 >= SERIALPORT_TIMEOUT) break;
    }
    return 0;
}
