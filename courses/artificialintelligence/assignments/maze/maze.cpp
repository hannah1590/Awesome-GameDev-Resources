// add your imports here
#include <iostream>
#include <map>
#include <vector>
#include <stack>
using namespace std;

int getRandom(unsigned int index)
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

    map<pair<int,int>, string> walls;
    map<pair<int,int>, bool> maze;
    stack<pair<int,int>> stack;
    vector<pair<int,int>> currentNeighbors;

    // makes walls of the maze
    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < columns; x++)
        {
            walls[make_pair(x,y)] = "_|";
        }
    }

    // sets up each maze coord
    for(int x = 0; x < columns; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            maze[make_pair(x,y)] = false;
        }
    }

    stack.emplace(0, 0);
    maze[make_pair(0,0)] = true;

    int currentX = 0;
    int currentY = 0;

    while(!stack.empty())
    {
        currentX = stack.top().first;
        currentY = stack.top().second;

        if(currentY - 1 >= 0 && !maze[make_pair(currentX,currentY - 1)])
        {
            currentNeighbors.emplace_back(currentX,currentY - 1);
        }
        if(currentX + 1 < columns && !maze[make_pair(currentX + 1,currentY)])
        {
            currentNeighbors.emplace_back(currentX + 1,currentY);
        }
        if(currentY + 1 < rows && !maze[make_pair(currentX,currentY + 1)])
        {
            currentNeighbors.emplace_back(currentX,currentY + 1);
        }
        if(currentX - 1 >= 0 && !maze[make_pair(currentX - 1,currentY)])
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

            if(currentNeighbors[random].second == currentY - 1)
            {
                walls[make_pair(currentX, currentY - 1)][0] = ' ';
            }
            else if(currentNeighbors[random].first == currentX + 1)
            {
                walls[make_pair(currentX, currentY)][1] = ' ';
            }
            else if(currentNeighbors[random].second == currentY + 1)
            {
                walls[make_pair(currentX, currentY)][0] = ' ';
            }
            else if(currentNeighbors[random].first == currentX - 1)
            {
                walls[make_pair(currentX - 1, currentY)][1] = ' ';
            }
            stack.push(currentNeighbors[random]);
            maze[currentNeighbors[random]] = true;
        }
        else if (currentNeighbors.size() == 1)
        {
            if(currentNeighbors[0].second == currentY - 1)
            {
                walls[make_pair(currentX, currentY - 1)][0] = ' ';
            }
            else if(currentNeighbors[0].first == currentX + 1)
            {
                walls[make_pair(currentX, currentY)][1] = ' ';
            }
            else if(currentNeighbors[0].second == currentY + 1)
            {
                walls[make_pair(currentX, currentY)][0] = ' ';
            }
            else if(currentNeighbors[0].first == currentX - 1)
            {
                walls[make_pair(currentX - 1, currentY)][1] = ' ';
            }

            stack.push(currentNeighbors[0]);
            maze[currentNeighbors[0]] = true;
        }
        else
        {
            stack.pop();
        }

        currentNeighbors.clear();
    }


    // prints out current state of walls
    for(int y = 0; y < rows; y++)
    {
       cout << " _";
    }
    cout << "  \n";
    for(int y = 0; y < rows; y++)
    {
        cout << "|";
        for (int x = 0; x < columns; x++) {
            cout << walls[make_pair(x, y)];
        }
        cout << " \n";
    }
}