//
// Created by yair on 14/1/20.
//

#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include <iostream>
#include "ClientHandler.h"
using namespace std;

namespace server_side {
    class Server {
    public:
        virtual void openServer(int port, ClientHandler* c) = 0;
        virtual void stopServer() = 0;
        virtual bool isOpen() = 0;
    };
}

#endif //MILESTONE2_SERVER_H
