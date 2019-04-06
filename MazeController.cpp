#include "MazeController.h"


void MazeController::solveMaze() {
    solution = new Stack();
    int startingRow = 1;
    int startingColumn = 0;

    //Add the starting position to the stack then
    //Read the position of the top of the solution stack and set a path character
    solution->Push(new Position(startingRow, startingColumn));
    maze[solution->Peek()->row][solution->Peek()->col] = pathChar;

    printMaze();

    do {
        //Check if there is an unexplored path. If there is, move to it
        //Prioritize movement in order: up - right- down - left
        //The sample mazes always start in the top left and end in the bottom right
        if (getCharUp() == ' ') {
            moveUp();
        }
        else if (getCharRight() == ' ') {
            moveRight();
        }
        else if (getCharDown() == ' '){
            moveDown();
        }
        else if (getCharLeft() == ' '){
            moveLeft();
        }

        //If no move has been made the pointer is either stuck or in a deadend.
        else
        {
            //Catch endless loop or seg faults in case the pointer goes back to the start of the maze.
            //If this fires, the maze is either unsolvable or there is an error in the moving logic.
            if(solution->Peek()->row == startingRow &&
               solution->Peek()->col == startingColumn)
            {
                cout << "The maze could not be solved." << endl;
                break;
            }

            //If no move is possible then there is a deadend
            //Mark this spot as a deadend and Pop this node from the stack
            maze[solution->Peek()->row][solution->Peek()->col] = deadendChar;
            solution->Pop();
        }
    }
    while(!checkWinCondition());
}

char **MazeController::parseMazeFile()
{
    string line;

    //Try to open the file
    try {
        fs.open(filePath);
    }
    catch (exception) {
        cout << "Failed to open the source file." << endl;
    };

    //File successfully opened
    if (fs.is_open())
    {
        startOfFile = fs.tellg();

        cout << endl << "Loading Maze..." << endl;

        //Referenced this to get the # of rows in the file - https://stackoverflow.com/questions/3072795/how-to-count-lines-of-a-file-in-c
        //Read each line of the file and count the # of lines.
        //Add 1 to get an accurate rowCount since this returns 1 less than needed.
        rowCount = count(istreambuf_iterator<char>(fs),
                         istreambuf_iterator<char>(), '\n') + 1;

        //Set the pointer to the start of the file
        fs.seekg(startOfFile,ios_base::beg);

        //Get the text of the first line to count the # of columns
        getline(fs, line);
        //Get the length of the line
        colCount = line.length();

        //Reset pointer to the beginning of the file
        fs.seekg(startOfFile,ios_base::beg);

        //Use the dynamic array size values to create and iterate through a 2D array
        //Each cell of the 2D array will contain 1 character of the text maze.
        fs.close();
        initiateMaze();
    }
    return nullptr;
}

void MazeController::initiateMaze()
{
    string line;
    int row = 0;

    //Create the 2D array using the dynamic row and col counts they have been collected.
    maze = new char*[rowCount];

    //Loop through the 1D array and assign another array to each cell.
    for(int i=0; i<rowCount; i++)
    {
        maze[i] = new char[colCount]; // maze[row][col]
    }

    try {
        fs.open(filePath);
    }
    catch (exception) {
        cout << "Failed to open the source file." << endl;
    }

    //File successfully opened
    if (fs.is_open()) {

        //Reset pointer to the beginning of the file
        fs.seekg(startOfFile,ios_base::beg);

        //Read through the file line by line
        while (!fs.eof()) {

            //Read the current line and assign is to a variable as a string
            getline(fs, line);

            //For each line of text, iterate through each array and set characters one-by-one until the line is finished.
            for (int i = 0; i < line.length(); i++) {
                //Get the current index of the character in the line of text and set that value to the equal index of the array.
                maze[row][i] = line.at(i);
            }
            row++; //Move onto the next row when the current row is finished.
        }
    }

    fs.close();
}

void MazeController::validateInput()
{
    bool validInput = false;
    int selection;

    do {
        cout << "Select which maze you want to solve:" << endl;
        cout << " - Type 1 to solve Maze 1." << endl;
        cout << " - Type 2 to solve Maze 2." << endl;
        cout << " - Type 3 to solve Maze 3." << endl;
        cout << " - Type 4 to solve Maze 4." << endl;
        cout << " - Type 5 to solve Maze X." << endl << ">>";

        cin >> selection;

        //Catch failed int input and retry.
        while (cin.fail()) {
            cout << endl << "Invalid input. Only numbers between 1-5 are valid options." << endl << ">>";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> selection;
        }

        if (selection > 0 && selection < 6) {
            validInput = true;
        } else {
            cout << "Selection out of range. Choose a maze by typing a selection between 1-5." << endl << endl;
            validInput = false;
        }
    } while (!validInput);

    string folderName = "mazes/";
    string fileName;

    string mazeNames[5] = {"maze.txt",
                           "maze2.txt",
                           "maze3.txt",
                           "maze4.txt",
                           "mazex.txt",
    };

    switch (selection) {
        case 1:
            fileName = mazeNames[0];
            break;

        case 2:
            fileName = mazeNames[1];
            break;

        case 3:
            fileName = mazeNames[2];
            break;

        case 4:
            fileName = mazeNames[3];
            break;

        case 5:
            fileName = mazeNames[4];
            break;
    }
    filePath = folderName + fileName;
}

//Once the maze is complete, print the maze and save to a text file.
void MazeController::saveMaze()
{
    //Try to open the save file to save the solution to.
    try
    {
       saveFile.open("mazes/mazeSolution.txt");
    }
    catch(const char *errorcode)
    {
        errorcode = "Failed to open/create the save file.";
        cout << errorcode << endl;
    }

    //If the file opens, save the solution to the file.
    if(saveFile.is_open())
    {
        try
        {
            for(int r=0; r<rowCount; r++)
            {
                for(int c=0; c<colCount; c++)
                {
                    saveFile << maze[r][c];
                }
                saveFile << endl;
            }
        }
        catch (const char* error)
        {
            error = "Error when writing to save file.";
            cout << error << endl;
        }
        saveFile.close();
    }
}

void MazeController::printMaze()
{
    //Remove all deadend symbols before printing the maze
    cleanMaze();

    cout << endl;
    for (int r=0; r<rowCount; r++)
    {
        for (int c=0; c<colCount; c++)
        {
            cout << maze[r][c];
        }
        cout << endl;
    }
}

void MazeController::cleanMaze()
{
    for (int r=0; r<rowCount; r++)
    {
        for (int c=0; c<colCount; c++)
        {
            if (maze[r][c] == '!')
            {
                maze[r][c] = ' ';
            }
        }
    }
}

bool MazeController::checkWinCondition()
{
    //Checks the cell of the maze that denotes the endgoal.
    //If the stack is reading this cell, the maze is complete.
    return (solution->Peek()->row == rowCount-2
         && solution->Peek()->col == colCount-1);
}

/**
 * Below are the functions used to check surrounding cells and to handle movement.
 */

char MazeController::getCharUp() {
    //Get the value from the row above in the same column
    return maze[solution->Peek()->row-1][solution->Peek()->col];
}

char MazeController::getCharRight() {
    //Get the value from the column to the right in the same row
    return maze[solution->Peek()->row][solution->Peek()->col+1];
}

char MazeController::getCharDown() {
    //Get the value from the row below in the same column
    return maze[solution->Peek()->row+1][solution->Peek()->col];
}

char MazeController::getCharLeft() {
    //Get the value from the column to the left in the same row
    return maze[solution->Peek()->row][solution->Peek()->col-1];
}

void MazeController::moveUp() {
    //New position = current row -1 to go up. column stays the same.
    solution->Push( new Position(solution->Peek()->row - 1, solution->Peek()->col) );

    maze[solution->Peek()->row][solution->Peek()->col] = pathChar;
    checkWinCondition();
}

void MazeController::moveRight() {
    //New position = row stays the same. column +1 to go right.
    solution->Push( new Position(solution->Peek()->row, solution->Peek()->col + 1) );

    maze[solution->Peek()->row][solution->Peek()->col] = pathChar;
    checkWinCondition();
}

void MazeController::moveDown() {
    //New position = current row +1 to go down. column stays the same.
    solution->Push( new Position(solution->Peek()->row + 1, solution->Peek()->col) );

    maze[solution->Peek()->row][solution->Peek()->col] = pathChar;
    checkWinCondition();
}

void MazeController::moveLeft() {
    //New position = row stays the same. column -1 to go right.
    solution->Push( new Position(solution->Peek()->row, solution->Peek()->col - 1) );

    maze[solution->Peek()->row][solution->Peek()->col] = pathChar;
    checkWinCondition();
}