/**
 *        @file: nw.cc
 *      @author: Drew VanAtta
 *        @date: February 11, 2025
 *       @brief: Implementation of Needleman-Wunsch algorithm
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Instead of making an entire other matrix, just store both the value and direction in one spot
struct Cell
{
    int val;
    int dir; // 1 = diagonal, 2 = left, 3 = up. 0 is the placeholder for the first row and column
};

// function declarations
void outputMatrix(Cell **matrix, int sx, int sy, string x, string y, string type);
void initMatrix(Cell **matrix, int sx, int sy, int gap);
void doNW(Cell **matrix, int sx, int sy, string x, string y, int gap, int match, int mismatch);

int main(int argc, char const *argv[])
{
    // Variables
    string x, y, input;
    int sx, sy, gap = -2, match = 1, mismatch = -1;

    // Get the sequences from input
    cout << "Enter seqeuence 1: ";
    cin >> y;
    cout << "Enter seqeuence 2: ";
    cin >> x;

    // Get the scoring values
    cout << "Default values: gap = -2, match = 1, mismatch = -1" << endl;
    cout << "Do you want to use the default values? (y/n): ";
    cin >> input;
    if (input == "n" || input == "N" || input == "no" || input == "No")
    {
        cout << "Enter the gap penalty: ";
        cin >> gap;
        cout << "Enter the match score: ";
        cin >> match;
        cout << "Enter the mismatch penalty: ";
        cin >> mismatch;
    }

    // Get the size of the sequences
    sx = x.size();
    sy = y.size();


    // Create the matrix - a pointer to a pointer of Cells
    Cell **matrix = new Cell *[sx + 1];

    for (int i = 0; i < sx + 1; i++)
    {
        // Allocate memory for the rows
        matrix[i] = new Cell[sy + 1];
    }

    // Initialize the matrix
    initMatrix(matrix, sx, sy, gap);
    doNW(matrix, sx, sy, x, y, gap, match, mismatch);
    
    outputMatrix(matrix, sx, sy, x, y, "val");
    cout << "----------------------------------------" << endl;
    outputMatrix(matrix, sx, sy, x, y, "dir");

    // CLEAR MEMORY
    for (int i = 0; i < sx + 1; i++)
    {
        // Free the row
        delete[] matrix[i];
    }
    // Free the matrix itself
    delete[] matrix;

    return 0;
} // main

void outputMatrix(Cell **matrix, int sx, int sy, string x, string y, string type)
{
    // This might not work on larger sequences, but used for early debugging, and showing off smaller sequences
    cout << setw(8) << " ";
    for (int i = 0; i < sy; i++)
    {
        cout << setw(4) << y[i];
    }
    cout << endl;

    for (int i = 0; i < sx + 1; i++)
    {
        if (i > 0)
        {
            cout << setw(4) << x[i - 1];
        }
        else
        {
            cout << setw(4) << " ";
        }
        for (int j = 0; j < sy + 1; j++)
        {
            cout << setw(4);
            if (type == "dir")
            {
                cout << matrix[i][j].dir;
            }
            else
            {
                cout << matrix[i][j].val;
            }
        }
        cout << endl;
    }
}

void initMatrix(Cell **matrix, int sx, int sy, int gap)
{
    // First column of the matrix
    for (int i = 0; i < sx + 1; i++)
    {
        matrix[i][0].val = i * gap;
    }
    // First row of the matrix
    for (int j = 0; j < sy + 1; j++)
    {
        matrix[0][j].val = j * gap;
    }
}

void doNW(Cell **matrix, int sx, int sy, string x, string y, int gap, int match, int mismatch)
{
    int diagonal, left, up;
    for (int i = 1; i < sx + 1; i++)
    {
        for (int j = 1; j < sy + 1; j++)
        {
            // Get the three values
            if (x[i - 1] == y[j - 1])
            {
                // match
                diagonal = matrix[i - 1][j - 1].val + match;
            }
            else
            {
                // mismatch
                diagonal = matrix[i - 1][j - 1].val + mismatch;
            }
            left = matrix[i][j - 1].val + gap;
            up = matrix[i - 1][j].val + gap;

            // Need the max, but also need to store the direction
            // Can't just use max() since it won't know the direction
            if (diagonal >= left && diagonal >= up)
            {
                // diagonal greater than or equal to both left and up, use diagonal
                matrix[i][j].val = diagonal;
                matrix[i][j].dir = 1;
            }
            else if (left >= diagonal && left >= up)
            {
                // check left if not diagonal
                matrix[i][j].val = left;
                matrix[i][j].dir = 2;
            }
            else
            {
                // otherwise up must be the greatest of three, since diagonal and left are not
                matrix[i][j].val = up;
                matrix[i][j].dir = 3;
            }
        }
    }
}