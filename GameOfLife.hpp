/*
 * GameOfLife.cpp
 *
 *  Created on: Feb 18, 2019
 *      Author: Justin Kim
 *
 * This class models a society of cells growing according
 * to the rules of John Conway's Game of Life.
 *
 */
#ifndef GAMEOFLIFE_HPP_
#define GAMEOFLIFE_HPP_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// This class allows a society of cells to grow according
// to the rules from John Conway's Game of Life
class GameOfLife {

// --Data Member(s)
private:
    std::vector<std::vector<bool>> theSociety;

public:
    // Construct a board that is rows by cols size
    // with all elements set to false
    GameOfLife(unsigned long rows, unsigned long cols) {
        theSociety = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    }

    // Grow a cell at the given location
    void growCellAt(unsigned long row, unsigned long col) {
        if (row < theSociety.size() && col < theSociety[row].size())
            theSociety[row][col] = true;
    }

    // Check to see if a cell is at the given location
    bool cellAt(unsigned long row, unsigned long col) const {
        if (row < theSociety.size() && col < theSociety[row].size()) {
            return theSociety[row][col];
        }
        return false;
    }

    // Returns the colony as one big string
    std::string toString() const {
        std::string retString;
        int numCols = theSociety[0].size();
        for (auto row : theSociety) {
            for (auto col : row) {
                if (col)
                    retString.append("O");
                else
                    retString.append(".");
            }
            retString.append("\n");
        }
        return retString;
    }

    // Count the neighbors around the given location.
    // Use wraparound. A cell in row 0 has neighbors in
    // the last row if a cell is in the same column, or
    // the column to the left or right. In this example,
    // cell 0,5 has two neighbors in the last row, cell 2,8
    // has four neighbors, cell 2,0 has four neighbors,
    // cell 1,0 has three neighbors. The cell at 3,8 has
    // 3 neighbors. The potential location for a cell at 4,8
    // would have three neighbors.
    //
    // .....O..O    0   0 1 2 3 4 5 6       x at 2, 3
    // O........    1   0 1 2 3 4 5 6
    // O.......O    2   0 1 2 x 4 5 6
    // O.......O    3   0 1 2 3 4 5 6
    // ....O.O..    4   0 1 2 3 4 5 6
    //
    // The return values should always be in the range of 0 through 8.
    // return the number of neighbors around any cell using wrap around.
    int neighborCount(int row, int col) const {
        int maxRow = theSociety.size() - 1;
        int maxCol = theSociety[0].size() - 1;
        int count = 0;
        int x = 0;
        int y = 0;

        for (int i = -1; i < 2; i++) {
			// if the given row is the bottom row, wrap around to the top row
            if (row + i < 0)
                x = maxRow;
			// if the given row is the top row, wrap around to the bottom row
            else if (row + i > maxRow)
                x = 0;
            else
                x = row + i;
            for (int j = -1; j < 2; j++) {
				// if the given column is the left most column, wrap around to the right most column
                if (col + j < 0)
                    y = maxCol;
				// if the given column is the right most column, wrap around to the left most column
                else if (col + j > maxCol)
                    y = 0;
                else {
                    y = col + j;
                }
                if (!(x == row && y == col)) {
                    if (cellAt(x, y))
                        count++;
                }
            }
        }
        return count;
    }

    // Change the state to the next society of cells
    void update() {
        GameOfLife t0 = *this;
        int numRows = theSociety.size();
        int numCols = theSociety[0].size();
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (t0.cellAt(i, j)) {
                    if (t0.neighborCount(i, j) < 2 || t0.neighborCount(i, j) > 3)
                        theSociety[i][j] = false;
                } else {
                    if (t0.neighborCount(i, j) == 3)
                        theSociety[i][j] = true;
                }
            }
        }

    }
};

#endif
