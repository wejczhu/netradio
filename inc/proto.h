#ifndef _PROTO_H_
#define _PROTO_H_

#include <string>


#define MSG_CHANNEL_MAX 512
#define MAX_DATA 

class ProtoC
{


private:
    static constexpr string DEFAULT_MGROUP = "224.2.2.2";
    static constexpr string DEFAULT_RCVPORT = "1989";
    static constexpr int CHNNR = 100;
    static constexpr int LISTCHNID = 0;
    static constexpr int MINCHNID = 1;
    static constexpr int MAXCHNID = MINCHNID + CHNNR - 1;


    struct msg_channel_st
    {
        uint8_t mChannelId;
        uint8_t mData[1];

    };

    struct  msg_list_st
    {
        uint8_t chnid;
          
    };
    
}





#endif