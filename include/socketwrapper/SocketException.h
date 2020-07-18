//
// Created by tal on 18/07/2020.
//

#ifndef SOCKET_WRAPPER_SOCKETEXCEPTION_H
#define SOCKET_WRAPPER_SOCKETEXCEPTION_H

#include <exception>

class SocketException : public std::exception {
protected:
    std::string m_message;
    int m_error;
public:
    explicit SocketException(const char* message) : m_message(message), m_error(errno) {}
    std::string getMessage() {
        return m_message;
    }
    int getError() const {
        return m_error;
    }

};

#endif //SOCKET_WRAPPER_SOCKETEXCEPTION_H
