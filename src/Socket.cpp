//
// Created by tal on 22/07/2020.
//

#include "socketwrapper/Socket.h"

Socket::Socket(int descriptor, int domain, int type, int protocol) : m_af(domain), m_type(type), m_protocol(protocol),
                                                                     m_fd(descriptor) {
    assertSocket(m_fd, SOCKET_INIT_ERROR);
}

Socket::Socket(int domain, int type, int protocol) : Socket(socket(domain, type, protocol), domain, type, protocol) {}

void Socket::bind(const char *ip, int port) const {
    struct sockaddr_in address = createAddress(m_af, ip, port);
    assertSocket(::bind(m_fd, (struct sockaddr *) &address, sizeof address), SOCKET_BIND_ERROR);
}

void Socket::listen(int listeners) const {
    assertSocket(::listen(m_fd, listeners), SOCKET_LISTEN_ERROR);
}

std::tuple<Socket, const char *> Socket::accept() const {
    int addressSize = sizeof(struct sockaddr_in);
    struct sockaddr_in clientAddress{};
    Socket client = wrapFileDescriptor(::accept(m_fd, (struct sockaddr *) &clientAddress, (socklen_t *) &addressSize));
    return {client, inet_ntoa(clientAddress.sin_addr)};
}

void Socket::connect(const char *ip, int port) const {
    struct sockaddr_in clientAddress = createAddress(m_af, ip, port);
    assertSocket(::connect(m_fd, (struct sockaddr *) &clientAddress, sizeof clientAddress),
                 SOCKET_CONNECT_ERROR);
}

size_t Socket::send(const void *buffer, size_t length, int flags) const {
    size_t bytes;
    assertSocket(bytes = ::send(m_fd, buffer, length, flags), SOCKET_SEND_ERROR);
    return bytes;
}

size_t
Socket::sendto(const void *buffer, size_t length, int flags, struct sockaddr_in *address,
               socklen_t addressLength) const {
    size_t sent;
    assertSocket(sent = ::sendto(m_fd, buffer, length, flags, (struct sockaddr *) address, addressLength),
                 SOCKET_SEND_ERROR);
    return sent;
}

size_t Socket::recv(void *buffer, size_t length, int flags) const {
    size_t received;
    assertSocket(received = ::recv(m_fd, buffer, length, flags), SOCKET_RECEIVE_ERROR);
    return received;
}

size_t
Socket::recvfrom(void *buffer, size_t length, int flags, struct sockaddr_in *address, socklen_t *addressLength) const {
    size_t received;
    assertSocket(received = ::recvfrom(m_fd, buffer, length, flags, (struct sockaddr *) address, addressLength),
                 SOCKET_RECEIVE_ERROR);
    return received;
}

void Socket::close() const {
    assertSocket(::close(m_fd), SOCKET_CLOSE_ERROR);
}

Socket Socket::wrapFileDescriptor(int fd) {
    int domain, type, protocol, argSize = sizeof(int);
    getsockopt(fd, SOL_SOCKET, SO_DOMAIN, &domain, (socklen_t *) &argSize);
    getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, (socklen_t *) &argSize);
    getsockopt(fd, SOL_SOCKET, SO_PROTOCOL, &protocol, (socklen_t *) &argSize);
    return {fd, domain, type, protocol};
}

struct sockaddr_in Socket::createAddress(int domain, const char *ip, int port) {
    struct sockaddr_in target{};
    target.sin_family = domain;
    target.sin_port = htons(port);
    target.sin_addr.s_addr = inet_addr(ip);
    return target;
}

int Socket::getAddressFamily() const {
    return m_af;
}

int Socket::getType() const {
    return m_type;
}

int Socket::getProtocol() const {
    return m_protocol;
}

int Socket::getDescriptor() const {
    return m_fd;
}

void Socket::assertSocket(int expression, const char *message) {
    if (expression == SOCKET_ERROR) {
        throw SocketException(message);
    }
}

bool Socket::operator==(const Socket &other) const {
    return m_af == other.m_af && m_type == other.m_type && m_protocol == other.m_protocol && m_fd == other.m_fd;
}

bool Socket::operator!=(const Socket &other) const {
    return !(*this == other);
}

bool Socket::operator<(const Socket &other) const {
    return m_fd < other.m_fd;
}