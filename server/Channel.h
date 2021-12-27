#ifndef _H_CHANNEL_H_
#define _H_CHANNEL_H_

#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "proto.h"

class ChannelC
{
public:
    ChannelC();
    // ~ChannelC();

public:
    int ChannelCreateThread();
    int ChannelDestoryThread();
    static void* Handler(void* p);
    void Run();


    uint8_t mChannelId;
    pthread_t mChannelThread;

    struct ChannelMessageS
    {
        uint8_t id;
        uint8_t data[1];
    };

};





#endif