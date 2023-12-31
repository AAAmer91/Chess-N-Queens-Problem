// Chess8Queens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

#define boardSize 8

void placeQueens(char chessBoard[boardSize][boardSize], int row, int& solutionNum, ofstream& myfile);
bool isSafe(char chessBoard[boardSize][boardSize], int row, int col);

int main() {
    ofstream myfile;
    myfile.open("8QOut.txt");

    char chessBoard[boardSize][boardSize];
    int solutionNum = 0;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            chessBoard[i][j] = '_';
        }
    }

    placeQueens(chessBoard, 0, solutionNum, myfile);

    myfile << "found " << solutionNum << " solutions \n";
    myfile.close();

    return 0;
}

void placeQueens(char chessBoard[boardSize][boardSize], int row, int& solutionNum, ofstream& myfile) {
    if (row == boardSize) {
        // All queens are placed, print the solution
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                myfile << chessBoard[i][j] << ' ';
            }
            myfile << '\n';
        }
        myfile << '\n';
        solutionNum++;
        return;
    }

    for (int col = 0; col < boardSize; col++) {
        if (isSafe(chessBoard, row, col)) {
            chessBoard[row][col] = 'Q';
            placeQueens(chessBoard, row + 1, solutionNum, myfile);
            chessBoard[row][col] = '_'; // Backtrack
        }
    }
}

bool isSafe(char chessBoard[boardSize][boardSize], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (chessBoard[i][col] == 'Q') {
            return false; // Check column conflicts
        }
        if (col - (row - i) >= 0 && chessBoard[i][col - (row - i)] == 'Q') {
            return false; // Check diagonal conflicts
        }
        if (col + (row - i) < boardSize && chessBoard[i][col + (row - i)] == 'Q') {
            return false; // Check diagonal conflicts
        }
    }
    return true;
}
