//
// Created by yair on 15/1/20.
//


#ifndef MILESTONE2_MYCLIENTHANDLER_H
#define MILESTONE2_MYCLIENTHANDLER_H

#define LINE_SEPARATOR "@"

#include<vector>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "Searchable.h"
#include "MatrixBuilder.h"
#include "PairsMatrix.h"
#include "SearchSolverOA.h"
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

class MyClientHandler : public ClientHandler {
    Solver<Searchable<pair<int, int>>*, string> *solver;
    CacheManager<string, string> *cacheManager;
public:

    MyClientHandler(SearchSolverOA<Searchable<pair<int, int>>*, string, pair<int, int>> *solver, CacheManager<string, string> *cacheManager): solver(solver), cacheManager(cacheManager) {}
    /**
 * this function handles the client requests.
 * @param socket This is the file descriptor of the socket.
 */
    virtual void handleClient(int clientfd);
};


#endif //MILESTONE2_MYCLIENTHANDLER_H
