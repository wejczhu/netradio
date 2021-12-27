#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <getopt.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "proto.h"  
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <net/if.h>
//#include "client.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

#define IPSTRSIZE 100

#define DEFAULT_PLAYERCMD " /usr/bin/mplayer -   > /dev/null"

int main(int argc, char * argv[])
{

    int index = 0;
    int sd = 0;
    struct ip_mreqn mreq;//group setting
    struct sockaddr_in laddr; //local address
    int val;//set sockopt 
    int pd[2];
    pid_t pid;
    struct sockaddr_in server_addr;
    socklen_t serveraddr_len;
    int len;
    int chosenid;
    int ret = 0;

    struct sockaddr_in raddr;
    socklen_t raddr_len;

    char ipstr[IPSTRSIZE];

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd < 0)
    {
        perror("socket()");
        exit(0);
    }
    //multicast group 
    inet_pton(AF_INET, MULTIGROUP, &mreq.imr_multiaddr);
    //local address(self)
    inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);
    //local net card
    mreq.imr_ifindex = if_nametoindex("lo");
    if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("setsockopt()");
        exit(1);
    }
    val = 1;

    if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, &(val), sizeof(val)) < 0)
    {
        perror("setsockopt()");
        exit(1);
    }
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(DEFAULT_RCVPORT);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
    if(bind(sd, (sockaddr*)&laddr, sizeof(laddr)) < 0)
    {
        perror("bind()");
        exit(1);
    }

    // Fork a new process to play the media stream
    if(pipe(pd) < 0)
    {
        perror("pipe()");
        exit(1);
    }

    pid = fork();
    if(pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if(pid == 0)
    {
        close(sd);
        close(pd[1]);
        dup2(pd[0], 0);
        if(pd[0] > 0)
        {
            close(pd[0]);
        }

        execl("/bin/sh", "sh", "-c", DEFAULT_PLAYERCMD, NULL);
        perror("execl()");
        exit(1);
    }

    struct sockaddr_in remoteAddress;
    struct MessageS buf;
    socklen_t remoteAddressLen;
    remoteAddressLen = sizeof(remoteAddress);

    uint8_t data[1024];

    //int fd = open("./output.mp4", O_CREAT | O_WRONLY | O_APPEND, 0664);
    while (1)
    {
        int len = recvfrom(sd, &data, 1024, 0, (sockaddr*) &remoteAddress, &remoteAddressLen);
        //inet_ntop(AF_INET, &remoteAddress.sin_addr, ipstr, IPSTRSIZE);
        ssize_t nr = write(pd[1], &data, len);
        // ssize_t nr = write(fd, &data, (1024));
        // if(nr < 0)
        // {
        //     perror("write()");
        //     exit(1);
        // }
        // if(nr == 0)
        // {
        //     std::cout <<"finish to write" <<std::endl;
        //     break;
        // }
    }
    //close(fd);
}