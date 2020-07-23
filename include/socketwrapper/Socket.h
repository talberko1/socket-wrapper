//
// Created by tal on 22/07/2020.
//

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <iostream>
#include <cstring>
#include <tuple>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socketwrapper/SocketException.h"

class Socket {
protected:
    int m_domain;
    int m_type;
    int m_protocol;
    int m_fd;
    Socket(int fd, int domain, int type, int protocol);
public:
    Socket(int domain, int type, int protocol);
    void bind(const char* ip, int port) const;
    void listen(int listeners) const;
    std::tuple<Socket, const char*> accept() const;
    void connect(const char* ip, int port) const;
    unsigned long send(const char *message, size_t length, int flags=0) const;
    unsigned long recv(char* buffer, unsigned long bytes, int flags=0) const;
    void close() const;
    static Socket wrapFileDescriptor(int fd);
};

#endif //SERVER_SOCKET_H
