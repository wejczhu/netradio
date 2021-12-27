#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/if.h>
//#include "server_conf.h"
#include "proto.h"
#include <string.h>
#include "Channel.h"
#include <sys/stat.h>
#include <fcntl.h>

static int SocketInit()
{
    struct sockaddr_in sndaddr;
    struct ip_mreqn mreq;
    inet_pton(AF_INET, MULTIGROUP, &mreq.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);//local address
    mreq.imr_ifindex = if_nametoindex("lo");//net card
    int serversd = socket(AF_INET, SOCK_DGRAM, 0);

    if(setsockopt(serversd, IPPROTO_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq)) < 0)
    {
        //syslog(LOG_ERR, "setsockopt(IP_MULTICAST_IF):%s", strerror(errno));
        perror("setsockopt()");
        exit(1);
    }

    //bind
    sndaddr.sin_family = AF_INET;
    sndaddr.sin_port = htons(DEFAULT_RCVPORT);
    inet_pton(AF_INET, MULTIGROUP, &sndaddr.sin_addr);
    //inet_pton(AF_INET, "0.0.0.0", &sndaddr.sin_addr.s_addr);
    
    return 0;
    
}


int main()
{
    //ChannelC ch = ChannelC();
    //ch.ChannelCreateThread();
    //ch.Run();

    // initialize socket 

    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd < 0)
    {
        perror("socket()");
        exit(1);
    }

    std::cout << "Create the socket" << std::endl;

    struct sockaddr_in groupSocket;
    struct in_addr localInterface;

    groupSocket.sin_family = AF_INET;
    groupSocket.sin_addr.s_addr = inet_addr(MULTIGROUP);
    groupSocket.sin_port = htons(DEFAULT_RCVPORT);

    int val = 1;

    struct ip_mreqn mreq;
    inet_pton(AF_INET, MULTIGROUP, &mreq.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address); 
    mreq.imr_ifindex = if_nametoindex("lo");

    int rel = setsockopt(sd, IPPROTO_IP ,IP_MULTICAST_IF, &mreq, sizeof(mreq));
    if(rel < 0)
    {
        perror("setopt()");
        exit(1);
    }

    //SocketInit();
    uint8_t data[128 * 1024];
    int fd = open("./test.mp4", O_RDONLY);
    if(fd == -1)
    {
        perror("open()");
        exit(1);
    }

    ssize_t nr;

    int speed = 1024;
    static int total = 0;
    for(;;)
    {
        nr = read(fd, &data, speed);
        //std::cout<<"nr: " << nr << std::endl;
        total += nr;
        if(nr == -1)
        {
            perror("read()");
            close(fd);
        }
        if(nr == 0)
        {
            std::cout << "finish to send data" << std::endl;
            break;
        }
 
        int result = sendto(sd, &data, nr, 0, (sockaddr*)&groupSocket, sizeof(groupSocket));
        if(result < 0)
        {
            perror("sendto()");
            exit(1);
        }

        usleep(1000 * 10); //sleep 10 ms 
    }
    std::cout << "total: " << total << std::endl;

    // int speed = 1024;
    // while(1)
    // {
    //     off_t curr = lseek(fd, 0, SEEK_CUR);
    //     std::cout << curr << std::endl;
    //     nr = read(fd, &data, speed);
    //     if(nr == -1)
    //     {
    //         perror("read()");
    //         close(fd);
    //     }
    //     curr = lseek(fd, 0, SEEK_CUR);
    //     std::cout << curr << std::endl;
        
    //     if(sendto(serversd, sbufp, len + sizeof(chnid_t), 0, (void*)&sndaddr, sizeof(sndaddr)) < 0)
    //     {
    //         syslog(LOG_ERR, "thr_channel(%d):sendto():%s", ent->chnid, strerror(errno));
    //         break;

    //     }
    //     sched_yield();
    // }



    //sleep(10);
}