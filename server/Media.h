#ifndef _H_MEDIA_H_
#define _H_MEDIA_H_

#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


#define PATHSIZE 1024
#define LINEBUFSIZE 1024
#define MP3_BITRATE 128 * 1024 // bps:128k

class MediaC
{
public:


public:
    //ssize_t ReadChannel(chnid_t chnid, void *buf, size_t size);

    uint8_t mChannelId;
    pthread_t mChannelThread;

    struct ChannelMessageS
    {
        uint8_t id;
        uint8_t data[1];
    };

};



#endif