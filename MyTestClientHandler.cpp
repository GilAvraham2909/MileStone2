//
// Created by yair on 16/1/20.
//
#define LINE_SEPARATOR "@"

#include "MyTestClientHandler.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include <thread>
#include <fstream>
#include <algorithm>
/**
 * this function handles the client requests.
 * @param socket This is the file descriptor of the socket.
 */
void MyTestClientHandler::handleClient(int clientfd) {
    char buffer[256];
    ssize_t n;
    int clientds = clientfd;
    string problem;
    vector<string> matrixVec;
    while (true) {
        bzero(buffer, 256);
        n = read(clientds, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        string clientBuffer = buffer;
        if ((clientBuffer == "end\n") || (clientBuffer == "end")) {
            break;
        }
        printf("Message: %s\n", buffer);
        clientBuffer += ",";
        vector<string> bufferPlex = lexer(clientBuffer, ',');
        bufferPlex.push_back(LINE_SEPARATOR);
        matrixVec.insert(matrixVec.end(), bufferPlex.begin(),
                          bufferPlex.end());
        bufferPlex.clear();
    }
    string solution;
    if (cacheManager->isThereSolution(problem)) {
        solution = cacheManager->getSolution(problem);
    } else {
        solution = solver->solve(problem);
        cacheManager->saveSolution(problem, solution);
    }
    const char *messgaec = solution.c_str();
    bzero(buffer, 256);
    strcpy(buffer, messgaec);
    n = write(clientds, buffer, strlen(buffer));
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    printf("Done\n");
}


