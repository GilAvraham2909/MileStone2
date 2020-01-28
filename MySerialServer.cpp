//
// Created by yair on 15/1/20.
//


#include "MySerialServer.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include <thread>
#include <fstream>
/**
 * this is  the function that operates the  server thread fuction.
 * @param port the port of the communication.
 * @param clientHandler this is the class that handles the client requests.
 */
void MySerialServer::open(int port, ClientHandler* clientHandler) {
    int clientNum = 5;
    thread serverThread(createServer, port, clientHandler, clientNum);
    serverThread.detach();
    }
/**
 * this is the thread func that handles the requests.
 * @param port the port of the comunication.
 * @param clientHandler this is the class that handles the client requests.
 * @param clientsnum number of clients.
 */
void MySerialServer::createServer(int port, ClientHandler *clientHandler, int clientsnum) {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        throw "Could not open socket";
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        throw "Could not bind socket";
    }
    listen(sockfd, clientsnum);
    clilen = sizeof(cli_addr);
    for (int i = 0; i< clientsnum; ++i) {
        cout<<"server Tries to connect"<<endl;
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                           (socklen_t *) &clilen);
        cout<<"server connection succeeded"<< endl;
        if (newsockfd < 0) {
            perror("couldn't accept client");
            exit(1);
        }
        cout<< "treating client number " << i <<endl;
        clientHandler->handleClient(newsockfd);
        cout<< "Client number: " << i <<" is done" <<endl;
    }

}

void MySerialServer::stop() {

}

