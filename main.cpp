//
// Created by yair on 14/1/20.
//

#include "MyParallelServer.h"
#include "SearcherInterface.h"
#include "Astar.h"
#include "CacheManager.h"
#include "MyClientHandler.h"
#include "DFS.h"
#include "BestFirstSearch.h"
int main(int argc, char* argv[]) {

    int port = stoi(argv[1]);
    server_side::MyParallelServer myParallelServer;
    SearcherInterface<pair<int, int>, string>* searcherInterface = new DFS<pair<int, int>, string>;
    SearchSolverOA<Searchable<pair<int, int>>*, string, pair<int, int>>* solver= new SearchSolverOA<Searchable<pair<int, int>>* , string, pair<int, int>>(searcherInterface);
    CacheManager<string, string>* cacheManager = new FileCacheManager;
    ClientHandler* clientHandler = new MyClientHandler(solver, cacheManager);
    myParallelServer.openServer(port, clientHandler);
    return 0;
}
