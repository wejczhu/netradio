#ifndef _CLIENT_H_
#define _CLIENT_H_

static constexpr char* DEFAULT_PLAYERCMD  = "/usr/bin/mplayer -   > /dev/null"

struct client_conf_st
{
    char *rcvport; // for local using
    char *mgroup;
    char *player_cmd;
};

#endif 