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

    void bind(const char *ip, int port) const;

    void listen(int listeners) const;

    std::tuple<Socket, const char *> accept() const;

    void connect(const char *ip, int port) const;

    size_t send(const char *message, size_t length, int flags = 0) const;

    size_t sendto(const char* message, size_t length, int flags, sockaddr_in address, socklen_t addressLength) const;

    size_t recv(char *buffer, unsigned long bytes, int flags = 0) const;

    size_t recvfrom(char* message, size_t length, int flags, sockaddr_in address, socklen_t* addressLength) const;

    void close() const;

    static Socket wrapFileDescriptor(int fd);

    bool operator==(const Socket& other) const;

    bool operator!=(const Socket& other) const;

    int getFD() const;

    int getAF() const;

    int getType() const;

    int getProtocol() const;

    static struct sockaddr_in createAddress(int domain, const char *ip, int port) ;
};

#endif //SERVER_SOCKET_H
