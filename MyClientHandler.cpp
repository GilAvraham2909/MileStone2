//
// Created by yair on 16/1/20.
//
#include "MyClientHandler.h"
/**
 * this function handles the client requests.
 * @param socket This is the file descriptor of the socket.
 */
void MyClientHandler::handleClient(int clientfd) {
    char buffer[1024];
    ssize_t n;
    int clientds = clientfd;
    string problem;
    vector<string> matrixToBe;
    while (true) {
        bzero(buffer, 1024);
        n = read(clientds, buffer, 1023);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        string strBuffer = buffer;
        if ((strBuffer == "end\n") || (strBuffer == "end")) {
            break;
        }
        strBuffer += ",";
        vector<string> lexedBuffer = lexer(strBuffer, ',');
        lexedBuffer.push_back(LINE_SEPARATOR);
        matrixToBe.insert(matrixToBe.end(), lexedBuffer.begin(),lexedBuffer.end());
        lexedBuffer.clear();
    }
    int probLength = (int) matrixToBe.size();
    for (int i = 0; i < probLength; ++i) {
        problem += matrixToBe[i];
    }
    string solution;
    if (cacheManager->isThereSolution(problem)) {
        solution = cacheManager->getSolution(problem);
    } else {
        MatrixBuilder* matrixBuilder = new MatrixBuilder;
        PairsMatrix *matrixOfPairs = matrixBuilder->createMatrix(matrixToBe);
        solution = solver->solve(matrixOfPairs);
        cacheManager->saveSolution(problem, solution);
        delete matrixOfPairs;
        delete matrixBuilder;
        matrixToBe.clear();
    }
    const char *messageCstyle = solution.c_str();
    bzero(buffer, 1024);
    strcpy(buffer, messageCstyle);
    n = write(clientds, buffer, strlen(buffer));
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    problem.clear();
    solution.clear();
    printf("Done\n");
    return;
}