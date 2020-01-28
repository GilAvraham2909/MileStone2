//
// Created by yair on 18/1/20.
//
#ifndef MILESTONE2_SOCKESTS_H
#define MILESTONE2_SOCKESTS_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <system_error>
#include <stdexcept>


namespace posix_sockets {
    class timeout_exception : public std::runtime_error {
    public:
        explicit timeout_exception(const char *msg) : std::runtime_error(msg) {}

        explicit timeout_exception(const std::string& msg) : std::runtime_error(msg) {}
    };

    class illegal_state_exception : public std::logic_error {
    public:
        explicit illegal_state_exception(const std::string& msg) : std::logic_error(msg) {}
    };
    struct TCP_socket {
        int sock_fd;

        TCP_socket() {
            sock_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (sock_fd < 0) {
                throw std::system_error(std::error_code(errno, std::generic_category()), "failure on opening socket");
            }
        }

        TCP_socket(int open_sock_fd) {
            this->sock_fd = open_sock_fd;
        }

        void close() {
            if (::close(sock_fd) < 0) {
                throw std::system_error(std::error_code(errno, std::generic_category()), "failure on closing socket");
            }
        }

        void settimeout(int sec, int usec = 0) {
            timeval timeout;
            timeout.tv_sec = sec;
            timeout.tv_usec = usec;
            if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO,
                           (char *) &timeout, sizeof(timeout)) == -1) {
                throw std::system_error(std::error_code(errno, std::generic_category()), "failure on setsockopt");
            }
        }
    };

    class TCP_client {
        TCP_socket sock;
    public:
        int get_socket() const {
            return sock.sock_fd;
        }
        explicit TCP_client(TCP_socket sock) : sock(sock) {}
        std::string read(int max_len) {
            char *buffer = new char[max_len + 1];
            int read_len = ::read(sock.sock_fd, buffer, max_len);
            if (read_len < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    throw timeout_exception("timeout on read");
                }
                throw std::system_error(std::error_code(errno, std::generic_category()), "error on read");
            }

            buffer[read_len] = 0;
            std::string output = std::string(buffer);
            delete[] buffer;
            return output;
        }

        void settimeout(int sec, int usec = 0) {
            sock.settimeout(sec, usec);
        }

        void close() {
            sock.close();
        }
    };

    class TCP_server {
        TCP_socket sock;
    public:
        TCP_server(int port) {
            int n = 1;
            setsockopt(sock.sock_fd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(int));
            sockaddr_in addr_in;
            addr_in.sin_family = AF_INET;
            addr_in.sin_port = htons(port);
            addr_in.sin_addr.s_addr = INADDR_ANY;

            if (bind(sock.sock_fd, (sockaddr *) &addr_in, sizeof(addr_in)) == -1) {
                throw std::system_error(std::error_code(errno, std::generic_category()), "failure on bind");
            }
        }

        void listen(int max_lis) {
            if (::listen(sock.sock_fd, max_lis) == -1) {
                throw std::system_error(std::error_code(errno, std::generic_category()), "error on listen");
            }
        }

        void settimeout(int sec, int usec = 0) {
            sock.settimeout(sec, usec);
        }

        TCP_client accept() {
            sockaddr_in addr;
            socklen_t len = sizeof(addr);
            int client_sock_fd = ::accept(sock.sock_fd, (sockaddr*) &addr, &len);
            if (client_sock_fd < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    throw timeout_exception("timeout on accept");
                } else {
                    throw std::system_error(std::error_code(errno, std::generic_category()), "error on accept");
                }
            }

            TCP_socket client_sock(client_sock_fd);
            client_sock.settimeout(0);
            return TCP_client(client_sock);
        }

        void close() {
            sock.close();
        }
    };
}

#endif //MILESTONE2_SOCKESTS_H
