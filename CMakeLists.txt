cmake_minimum_required(VERSION 3.13)
project(mileStone2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(mileStone2 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.cpp FileCacheManager.h StringReverser.cpp StringReverser.h State.h Searchable.h SearcherInterface.h Searcher.h BestFirstSearch.h StatesMatrix.h MatrixBuilder.cpp MatrixBuilder.h PairsMatrix.cpp PairsMatrix.h DFS.h BFS.h Astar.h Sockets.h MyParallelServer.cpp MyParallelServer.h SearchSolverOA.h MyClientHandler.cpp MyClientHandler.h)