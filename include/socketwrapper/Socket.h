//
// Created by tal on 18/07/2020.
//

#ifndef SOCKET_WRAPPER_SOCKET_H
#define SOCKET_WRAPPER_SOCKET_H

#include <string>
#include <cstring>
#include <tuple>
#include <exception>
#include <cerrno>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "SocketException.h"

class Socket {
private:
    Socket(int socketFileDescriptor, int domain, int type, int protocol);

    void init(int socketFileDescriptor, int domain, int type, int protocol);

    static void getSocketInitArguments(int socketFileDescriptor, int *domain, int *type, int *protocol);

protected:
    int m_socket{};
    int m_domain{};
    int m_type{};
    int m_protocol{};

    sockaddr_in createTargetAddress(std::string& ip, int port) const;

public:
    Socket(int domain, int type, int protocol);

    void bind(std::string& ip, int port);

    void listen(int listeners) const;

    std::pair<Socket, std::string> accept() const;

    void connect(std::string& ip, int port);

    long recv(int bytes) const;

    long send(std::string &message) const;

    void close() const;
};

#endif //SOCKET_WRAPPER_SOCKET_H
