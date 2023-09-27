// add your imports here
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;

int getRandom(int index)
{
    int random[] = {72, 99,  56,  34, 43, 62,31, 4, 70, 22,
                    6, 65, 96, 71, 29, 9,98, 41, 90, 7,
                    30,3,  97, 49, 63, 88,47, 82, 91, 54,
                    74,2,  86, 14, 58, 35,89, 11, 10, 60,
                    28,21, 52, 50, 55, 69,76, 94, 23, 66,
                    15,57, 44, 18, 67, 5, 24, 33, 77, 53, 
                    51,59, 20, 42, 80, 61, 1, 0, 38, 64,
                    45,92, 46, 79, 93, 95, 37, 40, 83, 13,
                    12,78, 75, 73, 84, 81, 8, 32, 27, 19,
                    87,85, 16, 25, 17, 68, 26, 39, 48, 36};
    return random[index];
}

int main() {
    // code here
    unsigned int columns;
    unsigned int rows;
    unsigned int index;

    cin >> columns >> rows >> index;

    map<pair<int,int>, char> walls;
    vector<pair<int,int>> maze;
    vector<pair<int,int>> visitedCells;
    vector<pair<int,int>> currentNeighbors;

    // makes walls of the maze
    for(int y = 0; y < rows + 1; y++)
    {
        for(int x = 0; x < (columns * 2 + 2); x++)
        {
            if(x % 2 == 0 && y != 0)
            {
                walls[make_pair(x,y)] = '|';
            }
            else if(x % 2 == 1 && x != columns * 2 + 1)
            {
                walls[make_pair(x,y)] = '_';
            }
            else
            {
                walls[make_pair(x,y)] = ' ';
            }
        }
    }

    // sets up each maze coord
    for(int x = 0; x < columns; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            maze.emplace_back(x,y);
        }
    }

    visitedCells.emplace_back(0,0);

    //while(!visitedCells.empty())
    //{
        int currentX = visitedCells.crbegin()->first;
        int currentY = visitedCells.crbegin()->second;
        if(currentY - 1 >= 0 && visitedCells.end() ==
                                    find(visitedCells.begin(), visitedCells.end(),make_pair(currentX,currentY - 1)))
        {
            currentNeighbors.emplace_back(currentX,currentY - 1);
        }
        if(currentX + 1 < columns && visitedCells.end() ==
                                     find(visitedCells.begin(), visitedCells.end(),make_pair(currentX + 1,currentY)))
        {
            currentNeighbors.emplace_back(currentX + 1,currentY);
        }
        if(currentY + 1 < rows && visitedCells.end() ==
                                  find(visitedCells.begin(), visitedCells.end(),make_pair(currentX,currentY + 1)))
        {
            currentNeighbors.emplace_back(currentX,currentY + 1);
        }
        if(currentX - 1 >= 0 && visitedCells.end() ==
                                find(visitedCells.begin(), visitedCells.end(),make_pair(currentX - 1,currentY)))
        {
            currentNeighbors.emplace_back(currentX - 1,currentY);
        }

        if(currentNeighbors.size() > 1)
        {
            int random = getRandom(index);
            index++;
            if(index > 99)
            {
                index = 0;
            }

            random = random % currentNeighbors.size();
            visitedCells.emplace_back(currentNeighbors[random]);
        }
        else if (currentNeighbors.size() == 1)
        {
            visitedCells.emplace_back(currentNeighbors[0]);
        }
        else
        {
            visitedCells.pop_back();
        }

        currentNeighbors.clear();
    //}

    for(auto p : currentNeighbors)
    {
        cout << p.first << p.second << endl;
    }

    // prints out current state of walls
    for(int y = 0; y < rows + 1; y++)
    {
        for (int x = 0; x < (columns * 2 + 2); x++)
        {
            cout << walls[make_pair(x,y)];
        }
        cout << "\n";
    }
}