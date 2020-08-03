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
     * Check the return values of sys/socket.h functions
     * if the return value in the expression parameter is SOCKET_ERROR (-1),
     * SocketException is thrown with the given message
     */
    static void assertSocket(int expression, const char *message);

public:

    /*
     * Create a new Socket of the given type, in the given domain, using the given protocol.
     * if the protocol is 0, one is chosen automatically.
     * Returns a new Socket object.
     * Throws a SocketException on error.
     */
    Socket(int domain, int type, int protocol);

    /*
     * Give the current Socket the local ip address and port number to bind to.
     * Throws a SocketException on error.
     */
    void bind(const char *ip, int port) const;

    /*
     * Prepare to accept connections on the current Socket.
     * the value passed in, listeners, is the amount of connection requests that will
     * be queued before further requests are refused.
     * Throws a SocketException on error.
     */
    void listen(int listeners) const;

    /*
     * Await a connection on the current Socket.
     * When a connection arrives, open a new Socket to communicate with it,
     * and return the new Socket and its address
     */
    std::tuple<Socket, const char *> accept() const;

    /*
     * Open a connection to the peer address at the given ip address and port number.
     */
    void connect(const char *ip, int port) const;

    /*
     * Send length amount of bytes of buffer to the current Socket.
     * Return the number of bytes sent.
     * Throws a SocketException on error.
     */
    size_t send(const void *buffer, size_t length, int flags) const;

    /*
     * Send length amount of bytes of buffer on the socket to peer at address (which is
     * addressLength bytes long).
     * Returns the number of bytes sent.
     * Throws a SocketException on error.
     */
    size_t sendto(const void *buffer, size_t length, int flags, sockaddr_in* address, socklen_t addressLength) const;

    /*
     * Read through the socket and fill buffer with length amount of bytes.
     * Returns the number of bytes read.
     * Throws a SocketException on error.
     */
    size_t recv(void *buffer, unsigned long bytes, int flags) const;

    /*
     * Read through the socket and fill buffer with length amount of bytes.
     * If address is not null, fill in *addressLength bytes of it with the address of
     * the sender, and store the actual size of the address in *addressLength.
     * Returns the number of bytes read.
     * Throws a SocketException on error.
     */
    size_t recvfrom(void *buffer, size_t length, int flags, sockaddr_in *address, socklen_t *addressLength) const;

    /*
     * Close the socket object
     * Throws a SocketException if the socket could not be closed
     */
    void close() const;

    /*
     * Method to wrap a file descriptor as a Socket object
     */
    static Socket wrapFileDescriptor(int descriptor);

    /*
     * Method to create a target address for the given
     * domain (address family), ip address and port number
     */
    static struct sockaddr_in createAddress(int domain, const char *ip, int port);

    /*
     * Get the socket address family.
     */
    int getAddressFamily() const;

    /*
     * Get the socket type.
     */
    int getType() const;

    /*
     * Get the socket protocol.
     */
    int getProtocol() const;

    /*
     * Get the socket file descriptor.
     */
    int getDescriptor() const;

    /*
     * Check if the fields of the current socket are
     * equal to the fields of the compared socket.
     */
    bool operator==(const Socket &other) const;

    /*
     * Check if the fields of the current socket are
     * not equal to the fields of the compared socket.
     */
    bool operator!=(const Socket &other) const;

    /*
     * Compare between the file descriptor of the current
     * socket to the file descriptor of the compared socket.
     */
    bool operator<(const Socket &other) const;
};

#endif //SERVER_SOCKET_H
