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

constexpr auto SOCKET_INIT_ERROR = "Failed to initialize socket";
constexpr auto SOCKET_BIND_ERROR = "Failed to bind address to socket";
constexpr auto SOCKET_LISTEN_ERROR = "Socket failed to start listening";
constexpr auto SOCKET_CONNECT_ERROR = "Failed to connect to target address";
constexpr auto SOCKET_SEND_ERROR = "Failed to send data";
constexpr auto SOCKET_RECEIVE_ERROR = "Failed to receive data";
constexpr auto SOCKET_CLOSE_ERROR = "Failed to close the socket";

class Socket {
protected:
    int m_af; /* Socket Address Family */
    int m_type; /* Socket Type */
    int m_protocol; /* Socket Protocol */
    int m_fd; /* Socket File Descriptor */

    /*
     * Protected constructor using an OPEN socket file descriptor.
     * Throws a SocketException if the descriptor is not valid.
     */
    Socket(int descriptor, int domain, int type, int protocol);

    /*
     * Checks the return values of sys/socket.h functions.
     * Throws a SocketException if the expression is equal to SOCKET_ERROR (-1).
     */
    static void assertSocket(int expression, const char *message);

public:

    /*
     * Creates a new Socket of the given type, in the given domain, using the given protocol.
     * if the protocol is 0, one is chosen automatically.
     * Returns a new Socket object.
     * Throws a SocketException on error.
     */
    Socket(int domain, int type, int protocol);

    /*
     * Gives the current Socket the local ip address and port number to bind to.
     * Throws a SocketException on error.
     */
    void bind(const char *ip, int port) const;

    /*
     * Prepares to accept connections on the current Socket.
     * the value passed in, listeners, is the amount of connection requests that will
     * be queued before further requests are refused.
     * Throws a SocketException on error.
     */
    void listen(int listeners) const;

    /*
     * Awaits a connection on the current Socket.
     * When a connection arrives, a new Socket is open to communicate with.
     * Returns the new Socket and its address.
     * Throws a SocketException on error.
     */
    std::tuple<Socket, const char *> accept() const;

    /*
     * Opens a connection to the peer address at the given ip address and port number.
     * Throws a SocketException on error.
     */
    void connect(const char *ip, int port) const;

    /*
     * Sends length amount of bytes of buffer to the current Socket.
     * Returns the number of bytes sent.
     * Throws a SocketException on error.
     */
    size_t send(const void *buffer, size_t length, int flags) const;

    /*
     * Sends length amount of bytes of buffer on the socket to peer at address (which is
     * addressLength bytes long).
     * Returns the number of bytes sent.
     * Throws a SocketException on error.
     */
    size_t sendto(const void *buffer, size_t length, int flags, sockaddr_in* address, socklen_t addressLength) const;

    /*
     * Reads through the socket and fills buffer with length amount of bytes.
     * Returns the number of bytes read.
     * Throws a SocketException on error.
     */
    size_t recv(void *buffer, size_t length, int flags) const;

    /*
     * Reads through the socket and fills buffer with length amount of bytes.
     * If address is not null, fills in *addressLength bytes of it with the address of
     * the sender, and stores the actual size of the address in *addressLength.
     * Returns the number of bytes read.
     * Throws a SocketException on error.
     */
    size_t recvfrom(void *buffer, size_t length, int flags, sockaddr_in *address, socklen_t *addressLength) const;

    /*
     * Closes the socket object
     * Throws a SocketException on error.
     */
    void close() const;

    /*
     * Wraps a file descriptor as a Socket object.
     */
    static Socket wrapFileDescriptor(int descriptor);

    /*
     * Creates a target address for the given domain (address family),
     * ip address and port number.
     */
    static struct sockaddr_in createAddress(int domain, const char *ip, int port);

    /*
     * Gets the socket address family.
     */
    int getAddressFamily() const;

    /*
     * Gets the socket type.
     */
    int getType() const;

    /*
     * Gets the socket protocol.
     */
    int getProtocol() const;

    /*
     * Gets the socket file descriptor.
     */
    int getDescriptor() const;

    /*
     * Checks if the fields of the current socket are
     * equal to the fields of the compared socket.
     */
    bool operator==(const Socket &other) const;

    /*
     * Checks if the fields of the current socket are
     * not equal to the fields of the compared socket.
     */
    bool operator!=(const Socket &other) const;

    /*
     * Compares between the file descriptor of the current
     * socket to the file descriptor of the compared socket.
     */
    bool operator<(const Socket &other) const;
};

#endif //SERVER_SOCKET_H
