#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int ROWS = 10;
const int COLS = 10;
char grid[ROWS][COLS];

void floodFill(int r, int c, char fillChar)
{
    if(grid[r][c] == fillChar || grid[r][c] == 'X')
        return;

    else if(grid[r][c] != 'X')
    {
        grid[r][c] = fillChar;
        floodFill(r + 1, c, fillChar);
        floodFill(r, c + 1, fillChar);
        floodFill(r - 1, c, fillChar);
        floodFill(r, c - 1, fillChar);
    }

}

void print()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            cout << grid[i][j] << " ";    const int ROWS = 10;
    const int COLS = 10;
    char grid[ROWS][COLS];
        }
        cout << "\n";
    }
}

int main()
{
    srand(time(NULL));

    //Draw a grid with X around borders
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(i == 0 || j == 0 || i == ROWS - 1 || j == ROWS - 1)
                grid[i][j] = 'X';

            else
            {
                int gen = rand() % 2;
                if(gen == 0)
                    grid[i][j] = '.';
                else
                    grid[i][j] = 'X';
            }
        }
    }

    //Pick a "pixel" to start from
    int seedRow = 1;
    int seedCol = 1;
    char fillChar = '~';
    grid[seedRow][seedCol] = '.';

    cout << "Initial grid:\n";
    print();

    floodFill(seedRow, seedCol, fillChar);

    cout << "\n\nAfter filling at point (" << seedRow << ", " << seedCol << ") with " << fillChar << ":\n";
    print();

    return 0;
}
