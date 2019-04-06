#include <iostream>
#include "MazeController.h"

using namespace std;

int main() {

    MazeController mazeController = MazeController();
    bool solveAnother = true;
    char yesOrNo;

    do {
        //Validate the input, use a switch case to determine maze choice and return the filepath of the maze's txt file
        mazeController.validateInput();

        //Takes in a filepath, parses that txt file into a 2D char array.
        mazeController.parseMazeFile();

        //Solve the selected maze
        mazeController.solveMaze();

        //Print the solution
        mazeController.printMaze();

        //Save the solved maze to a text file.
        mazeController.saveMaze();

        cout << "Do you want to solve another maze? (Type 'n' to cancel)" << endl << ">>";
        cin >> yesOrNo;
        if (yesOrNo == 'n' || yesOrNo == 'N')
        {
            solveAnother = false;
            cout << "Closing program..." << endl;
        }
    }
    while (solveAnother);

    return 0;
}