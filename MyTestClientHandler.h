//
// Created by yair on 16/1/20.
//


#ifndef MILESTONE2_MYTESTCLIENTHANDLER_H
#define MILESTONE2_MYTESTCLIENTHANDLER_H

#include <vector>
#include "ClientHandler.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
class MyTestClientHandler : public ClientHandler{
Solver<string, string>* solver = new StringReverser;
CacheManager<string, string>* cacheManager = new FileCacheManager;

public:
    /**
 * this function handles the client requests.
 * @param socket This is the file descriptor of the socket.
 */
    virtual void handleClient(int clientfd);
};


#endif //MILESTONE2_MYTESTCLIENTHANDLER_H
