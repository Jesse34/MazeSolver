//
// Created by nscc on 2/14/18.
//

#ifndef ASS2_MAZESOLVER_MAZEREADER_H
#define ASS2_MAZESOLVER_MAZEREADER_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include "string"
#include "Stack.h"

using namespace std;

class MazeController
{
private:
    ifstream fs;
    ofstream saveFile;
    string filePath;
    int startOfFile;
    int rowCount = 0;
    int colCount = 0;

    char** maze;
    Stack* solution;

    char getCharUp();
    char getCharRight();
    char getCharDown();
    char getCharLeft();

    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();

    void cleanMaze();
    void initiateMaze();
    bool checkWinCondition();

public:
    char pathChar = '$';
    char deadendChar = '!';

    void validateInput();
    char** parseMazeFile();
    void printMaze();
    void solveMaze();
    void saveMaze();
};


#endif //ASS2_MAZESOLVER_MAZEREADER_H
