# Milestone 2

## About
This program revolves around the server client structure. in general this is a search engine for a given problem.  In this project we are given a Matrix NxN which is built from numbers that are inputted to our sever by the client. our job is to analyze the matrix is to find the fastest and cheapest way from a given starting point to the given destination point.

## Algorithems
in this project we use 4 different algorithms:

* DFS 

* BFS

* BestFirst search

* AStar

  we then send an output to our sever the appropriate solution with a direction matrix, just like a map.

  in addition we store every solution in our database both in Cache an in File caching allowing us fast access to solutions that already been solved before, Enjoy using our search engine !!

  ## Run
  in order to run the program, run this command in the terminal:

  ```
  g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
  ```

  our program requires an available port here is how to execute the program with a recommended port:

  ```
  ./a.out 5600
  ```

  Open terminal and enter the following command :

  ```
  telnet localhost 5600
  ```

  Enter the matrix right after enter the entry point and destination point in two different lines.

  Enter "end" when you finished and wait for answer from the server.

  Gil and Yair.
  
  ## Link
  - The GitHub that contain our project https://github.com/GilAvraham2909/MileStone2.git
