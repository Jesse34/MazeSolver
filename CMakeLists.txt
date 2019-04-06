cmake_minimum_required(VERSION 3.9)
project(Ass2_MazeSolver)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ass2_MazeSolver main.cpp MazeController.cpp MazeController.h Stack.cpp Stack.h StackNode.cpp StackNode.h Position.cpp Position.h)