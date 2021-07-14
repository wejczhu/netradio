#include "Media.h"




ssize_t MediaC::ReadChannel(chnid_t chnid, void *buf, size_t size)
{
    int tbfsize;
    int len;
    int next_ret = 0;
    //get token number
    tbfsize = mytbf_fetchtoken(channel[chnid].tbf, size);
    

    while(1)
    {
        len = pread(channel[chnid].fd, buf, tbfsize,channel[chnid].offset);
        /*current song open failed*/
        if(len < 0)
        {
            //当前这首歌可能有问题，错误不至于退出，读取下一首歌
            syslog(LOG_WARNING, "media file %s pread():%s", channel[chnid].mp3glob.gl_pathv[channel[chnid].pos], strerror(errno));
            open_next(chnid);
        }
        else if(len == 0)
        {
            syslog(LOG_DEBUG, "media %s file is over", channel[chnid].mp3glob.gl_pathv[channel[chnid].pos]);
            #ifdef DEBUG
                printf("current chnid :%d\n", chnid);
            #endif
            next_ret = open_next(chnid);
            break;
        }
        else/*len > 0*///真正读取到了数据
        {
            channel[chnid].offset += len;
            syslog(LOG_DEBUG, "epoch : %f", (channel[chnid].offset) / (16*1000*1.024));
            break;
        }
    }
    //remain some token
    if(tbfsize - len > 0)
        mytbf_returntoken(channel[chnid].tbf, tbfsize - len);
    return len;//返回读取到的长度

    
}