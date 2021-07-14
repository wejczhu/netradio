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

int main(int argc, char * argv[])
{

    /*
    initializing
    level:default < configuration file < 
          environment < arg

    */
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
    inet_pton(AF_INET, MULTIGROUP, &mreq.imr_multiaddr);//255.255.255.255-->0xFF..
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
    //improve efficiency
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


    struct sockaddr_in remoteAddress;
    struct MessageS buf;
    socklen_t remoteAddressLen;
    remoteAddressLen = sizeof(remoteAddress);


    uint8_t data[5 * 1024];
    //int data = 0;

    int fd = open("./output.mp3", O_CREAT | O_WRONLY);
    while (1)
    {
        std::cout << "11111111111" << std::endl;
        recvfrom(sd, &data, 1024, 0, (sockaddr*) &remoteAddress, &remoteAddressLen);
        std::cout << "222222222222" << std::endl;
        //inet_ntop(AF_INET, &remoteAddress.sin_addr, ipstr, IPSTRSIZE);

        ssize_t nr = write(fd, &data, (1024));
        if(nr < 0)
        {
            perror("write()");
            exit(1);
        }
        if(nr == 0)
        {
            std::cout <<"finish to write" <<std::endl;
            break;
        }
    }
    close(fd);
}