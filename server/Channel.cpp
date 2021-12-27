#include "Channel.h"


ChannelC::ChannelC()
: mChannelId(0)
, mChannelThread(0)
{
}


int ChannelC::ChannelCreateThread()
{

    int ret = pthread_create(&mChannelThread, NULL, Handler, NULL);
    if(ret)
    {
        perror("pthread_create()");
        exit(1);
    }
    return ret;
}

int ChannelC::ChannelDestoryThread()
{
    pthread_cancel(mChannelThread);
    pthread_join(mChannelThread, NULL);
    return 1;
}

void* ChannelC::Handler(void* p)
{
    while(1)
    {
        puts("channel hander");
    }
}


void ChannelC::Run()
{
    pthread_detach(mChannelThread);
}

