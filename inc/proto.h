#ifndef _PROTO_H_
#define _PROTO_H_

#include <string>


#define MSG_CHANNEL_MAX 512
#define MAX_DATA 
#define NAME_SIZE 50

using namespace std;

static const char* MULTIGROUP = "224.2.2.2";
static const uint16_t DEFAULT_RCVPORT = 1989;
static constexpr int CHNNR = 100;
static constexpr int LISTCHNID = 0;
static constexpr int MINCHNID = 1;
static constexpr int MAXCHNID = MINCHNID + CHNNR - 1;


struct MessageS
{
    char name[NAME_SIZE];
    uint32_t math;
    uint32_t chinese;
};

#endif