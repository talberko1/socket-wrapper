//
// Created by tal on 22/07/2020.
//

#include "socketwrapper/Socket.h"

void assertSocket(int expression, const char *message);

struct sockaddr_in createAddress(int domain, const char *ip, int port);

Socket::Socket(int domain, int type, int protocol) : Socket(socket(domain, type, protocol), domain, type, protocol) {}

Socket::Socket(int fd, int domain, int type, int protocol) : m_domain(domain), m_type(type), m_protocol(protocol),
                                                             m_fd(fd) {
    assertSocket(m_fd, "Failed to initialize socket");
}

void Socket::bind(const char *ip, int port) const {
    struct sockaddr_in address = createAddress(m_domain, ip, port);
    assertSocket(::bind(m_fd, (struct sockaddr *) &address, sizeof address), "Failed to bind address to socket");
}

void Socket::listen(int listeners) const {
    assertSocket(::listen(m_fd, listeners), "Socket failed to start listening");
}

std::tuple<Socket, const char *> Socket::accept() const {
    int addressSize = sizeof(struct sockaddr_in);
    struct sockaddr_in clientAddress{};
    Socket client = wrapFileDescriptor(::accept(m_fd, (struct sockaddr *) &clientAddress, (socklen_t *) &addressSize));
    return {client, inet_ntoa(clientAddress.sin_addr)};
}

void Socket::connect(const char *ip, int port) const {
    struct sockaddr_in clientAddress = createAddress(m_domain, ip, port);
    assertSocket(::connect(m_fd, (struct sockaddr *) &clientAddress, sizeof clientAddress),
                 "Failed to connect to target address");
}

unsigned long Socket::send(const char *message, size_t length, int flags) const {
    size_t bytes;
    assertSocket(bytes = ::send(m_fd, message, length, flags), "Failed to send data");
    return bytes;
}

unsigned long Socket::recv(char *buffer, size_t length, int flags) const {
    size_t received;
    assertSocket(received = ::recv(m_fd, buffer, length, flags), "Failed to receive data");
    return received;
}

void Socket::close() const {
    assertSocket(::close(m_fd), "Failed to close the socket");
}

Socket Socket::wrapFileDescriptor(int fd) {
    int domain, type, protocol, argSize = sizeof(int);
    getsockopt(fd, SOL_SOCKET, SO_DOMAIN, &domain, (socklen_t *) &argSize);
    getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, (socklen_t *) &argSize);
    getsockopt(fd, SOL_SOCKET, SO_PROTOCOL, &protocol, (socklen_t *) &argSize);
    return {fd, domain, type, protocol};
}


void assertSocket(int expression, const char *message) {
    if (expression == SOCKET_ERROR) {
        throw SocketException(message);
    }
}

struct sockaddr_in createAddress(int domain, const char *ip, int port) {
    struct sockaddr_in target{};
    target.sin_family = domain;
    target.sin_port = htons(port);
    target.sin_addr.s_addr = inet_addr(ip);
    return target;
}

bool Socket::operator==(const Socket &other) const {
    return m_domain == other.m_domain && m_type == other.m_type && m_protocol == other.m_protocol && m_fd == other.m_fd;
}

bool Socket::operator!=(const Socket &other) const {
    return !(*this == other);
}

int Socket::getAF() const {
    return m_domain;
}

int Socket::getType() const {
    return m_type;
}

int Socket::getProtocol() const {
    return m_protocol;
}

int Socket::getFD() const {
    return m_fd;
}