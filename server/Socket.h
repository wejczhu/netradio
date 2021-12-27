#ifndef _SOCKET_H_
#define _SOCKET_H_

class SocketC
{
    SocketC() = default;
    ~Socket() = default;

    Socket(const SocketC&) = delete;
    &SocketC operator=(const SocketC&) = delete;

private:
    void Init();
};


#endif