//
// Created by tal on 18/07/2020.
//
#include "socketwrapper/Socket.h"

Socket::Socket(int socketFileDescriptor, int domain, int type, int protocol) {
    m_socket = socketFileDescriptor;
    m_domain = domain;
    m_type = type;
    m_protocol = protocol;
    if (m_socket == -1) {
        throw SocketException("Failed to create socket");
    }
}

Socket::Socket(int domain, int type, int protocol) : Socket(socket(domain, type, protocol), domain, type, protocol){}

void Socket::getSocketInitArguments(int socketFileDescriptor, int *domain, int *type, int *protocol) {
    int argSize = sizeof(int);
    getsockopt(socketFileDescriptor, SOL_SOCKET, SO_DOMAIN, &domain, (socklen_t *) &argSize);
    getsockopt(socketFileDescriptor, SOL_SOCKET, SO_TYPE, &type, (socklen_t *) &argSize);
    getsockopt(socketFileDescriptor, SOL_SOCKET, SO_PROTOCOL, &protocol, (socklen_t *) &argSize);
}

sockaddr_in Socket::createTargetAddress(std::string& ip, int port) const {
    sockaddr_in targetAddress{};
    memset(&targetAddress, 0, sizeof(targetAddress));
    targetAddress.sin_family = m_domain;
    targetAddress.sin_addr.s_addr = inet_addr(ip.c_str());
    targetAddress.sin_port = htons(port);
    return targetAddress;
}

void Socket::bind(std::string& ip, int port) {
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
    int client_socket = ::accept(m_socket, (sockaddr *) &client_address, (socklen_t *) &address_size);
    if (client_socket != -1) {
        int domain, type, protocol;
        Socket::getSocketInitArguments(client_socket, &domain, &type, &protocol);
        Socket client = Socket(client_socket, domain, type, protocol);
        return std::pair<Socket, std::string>(client, inet_ntoa(client_address.sin_addr));
    }
    throw SocketException("Unable to accept incoming socket");
}

void Socket::connect(std::string& ip, int port) {
    sockaddr_in targetAddress = createTargetAddress(ip, port);
    if (::connect(m_socket, (sockaddr *) &targetAddress, sizeof(targetAddress)) < 0) {
        throw SocketException("Could not connect to target machine");
    }
}

long Socket::send(std::string &message) const {
    int status = ::send(this->m_socket, message.c_str(), message.size() + 1, 0);
    if (status == -1) {
        throw SocketException("Failed to send data");
    }
    return status;
}

long Socket::recv(int bytes) const {
    char *buffer = new char[bytes + 1];
    memset(buffer, 0, bytes + 1);
    int status = ::recv(this->m_socket, buffer, sizeof(buffer), 0);
    if (status == -1) {
        throw SocketException("Failed to receive data");
    }
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