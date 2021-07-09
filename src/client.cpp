#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>

int main(int argc, char* argv[])
{

    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd < 0)
    {
        perror("socket():");
        exit(1);
    }
    pipe();

    fork();




    exit(0);
}