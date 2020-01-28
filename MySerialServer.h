//
// Created by yair on 15/1/20.
//


#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H

#include "Server.h"

using namespace server_side;
class MySerialServer : public Server {
public:
    static int serverSocket;
    int clientSocket;
    virtual void open(int port, ClientHandler* clientHandler);
    void static createServer(int port, ClientHandler* clientHandler, int clientsNum);
    virtual void stop();
};


#endif //MILESTONE2_MYSERIALSERVER_H
