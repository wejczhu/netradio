#ifndef _SERVER_CONF_H_
#define _SERVER_CONF_H_


#define DEFAULT_MEDIADIR "/var/media/"
#define DEFAULT_IF "eth0"
#define 


struct server_conf_st
{
    char* rcvport;
    char* mgroup;
    char* media_dir;
    char runmode;
    char* ifname;
};


#endif