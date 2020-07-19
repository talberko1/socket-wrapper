//
// Created by tal on 18/07/2020.
//
#include "socketwrapper/Socket.h"

Socket::Socket(int socket_fd, int domain, int type, int protocol) :
        m_socket(socket_fd), m_domain(domain), m_type(type), m_protocol(protocol) {
    if (m_socket == -1) {
        throw SocketException("Failed to create socket");
    }
}

Socket::Socket(int domain, int type, int protocol) : Socket(socket(domain, type, protocol), domain, type, protocol) {}

Socket Socket::WrapFileDescriptor(int socket_fd) {
    int domain, type, protocol, argSize = sizeof(int);
    getsockopt(socket_fd, SOL_SOCKET, SO_DOMAIN, &domain, (socklen_t *) &argSize);
    getsockopt(socket_fd, SOL_SOCKET, SO_TYPE, &type, (socklen_t *) &argSize);
    getsockopt(socket_fd, SOL_SOCKET, SO_PROTOCOL, &protocol, (socklen_t *) &argSize);
    return {socket_fd, domain, type, protocol};
}

sockaddr_in Socket::createTargetAddress(std::string &ip, int port) const {
    sockaddr_in targetAddress{};
    memset(&targetAddress, 0, sizeof(targetAddress));
    targetAddress.sin_family = m_domain;
    targetAddress.sin_addr.s_addr = inet_addr(ip.c_str());
    targetAddress.sin_port = htons(port);
    return targetAddress;
}

void Socket::bind(std::string &ip, int port) {
    sockaddr_in hostAddress = createTargetAddress(ip, port);
    if (::bind(m_socket, (sockaddr *) &hostAddress, sizeof(hostAddress)) == -1) {
        throw SocketException("Failed to bind socket to given address");
    }
}

void Socket::listen(int listeners) const {
    if (::listen(m_socket, listeners) == -1) {
        throw SocketException("Failed to listen on the given port");
    }
}

std::pair<Socket, std::string> Socket::accept() const {
    sockaddr_in client_address{};
    int address_size = sizeof(client_address);
    memset(&client_address, 0, address_size);
    int client_fd = ::accept(m_socket, (sockaddr *) &client_address, (socklen_t *) &address_size);
    if (client_fd != -1) {
        Socket client_socket = WrapFileDescriptor(client_fd);
        return std::pair<Socket, std::string>(client_socket, inet_ntoa(client_address.sin_addr));
    }
    throw SocketException("Unable to accept incoming socket");
}

void Socket::connect(std::string &ip, int port) {
    sockaddr_in targetAddress = createTargetAddress(ip, port);
    if (::connect(m_socket, (sockaddr *) &targetAddress, sizeof targetAddress) < 0) {
        throw SocketException("Could not connect to target machine");
    }
}

long Socket::send(std::string &message) const {
    int status = ::send(m_socket, message.c_str(), message.size() + 1, 0);
    if (status == -1) {
        throw SocketException("Failed to send data");
    }
    return status;
}

long Socket::recv(int bytes, std::string &out) const {
    char buffer[bytes];
    memset(buffer, 0, bytes);
    int status = ::recv(m_socket, buffer, bytes, 0);
    if (status == -1) {
        throw SocketException("Failed to receive data");
    }
    if (status == 0) {
        return 0;
    }
    out = buffer;
    return status;
}

void Socket::close() const {
    if (::close(m_socket)) {
        throw SocketException("Failed to close socket");
    }
}

int Socket::getSocketFileDescriptor() const {
    return m_socket;
}

int Socket::getSocketAddressFamily() const {
    return m_domain;
}

int Socket::getSocketType() const {
    return m_type;
}

int Socket::getSocketProtocol() const {
    return m_protocol;
}