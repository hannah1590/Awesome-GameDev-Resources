#include "Catcher.h"

// for unordered map and sets with pairs
struct pairHash
{
public:
    size_t operator()(const pair<int,int> p) const
    {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

vector<pair<pair<int,int>,string>> Catcher::getValidNeighbors(pair<int,int> current, const vector<bool>& world, int sideSize, vector<pair<int, char>>& distances)
{
    int halfSideSize = sideSize / 2;
    vector<pair<pair<int,int>,string>> neighbors;
    int currentX = current.first + halfSideSize;
    int currentY = current.second + halfSideSize;

    // checks if cat is at a border
    bool northBorder = true;
    bool eastBorder = true;
    bool westBorder = true;
    bool southBorder = true;
    if(current.first + 1 <= halfSideSize)
        eastBorder = false;
    if(current.first - 1 >= -halfSideSize)
        westBorder = false;
    if(current.second + 1 <= halfSideSize)
        southBorder = false;
    if(current.second - 1 >= -halfSideSize)
        northBorder = false;

    if(current.second % 2 == 1)
    {
        if(!northBorder && !eastBorder && !world[(currentY - 1) * sideSize + (currentX + 1)]) // NE
            neighbors.emplace_back(make_pair(current.first + 1, current.second - 1), "NE");
        if(!northBorder && !world[(currentY - 1) * sideSize + (currentX)]) // NW
            neighbors.emplace_back(make_pair(current.first, current.second - 1), "NE");
        if(!eastBorder && !world[(currentY) * sideSize + (currentX + 1)]) // E
        {
            if(distances['N'] > distances['S'] && (!world[(currentY + 1) * sideSize + (currentX)] || !world[(currentY + 1) * sideSize + (currentX + 1)]))
                neighbors.emplace_back(make_pair(current.first + 1, current.second), "ES");
            else
                neighbors.emplace_back(make_pair(current.first + 1, current.second), "EN");
        }
        if(!westBorder && !world[(currentY) * sideSize + (currentX - 1)]) // W
        {
            if(distances['N'] > distances['S'] && (!world[(currentY + 1) * sideSize + (currentX)] || !world[(currentY + 1) * sideSize + (currentX + 1)]))
                neighbors.emplace_back(make_pair(current.first - 1, current.second), "WS");
            else
                neighbors.emplace_back(make_pair(current.first - 1, current.second), "WN");
        }
        if(!southBorder && !world[(currentY + 1) * sideSize + (currentX)]) // SE
            neighbors.emplace_back(make_pair(current.first, current.second + 1), "SE");
        if(!southBorder && !eastBorder && !world[(currentY + 1) * sideSize + (currentX + 1)]) // SW
            neighbors.emplace_back(make_pair(current.first + 1, current.second + 1), "SW");
    }
    else
    {
        if(!northBorder && !world[(currentY - 1) * sideSize + (currentX)]) // NE
            neighbors.emplace_back(make_pair(current.first, current.second - 1), "NE");
        if(!northBorder && !westBorder && !world[(currentY - 1) * sideSize + (currentX - 1)]) // NW
            neighbors.emplace_back(make_pair(current.first - 1, current.second - 1), "NE");
        if(!eastBorder && !world[(currentY) * sideSize + (currentX + 1)]) // E
        {
            if(distances['N'] > distances['S'] && (!world[(currentY + 1) * sideSize + (currentX - 1)] || !world[(currentY + 1) * sideSize + (currentX)]))
                neighbors.emplace_back(make_pair(current.first + 1, current.second), "ES");
            else
                neighbors.emplace_back(make_pair(current.first + 1, current.second), "EN");
        }
        if(!westBorder && !world[(currentY) * sideSize + (currentX - 1)]) // W
        {
            if(distances['N'] > distances['S'] && (!world[(currentY + 1) * sideSize + (currentX - 1)] || !world[(currentY + 1) * sideSize + (currentX)]))
                neighbors.emplace_back(make_pair(current.first - 1, current.second), "WS");
            else
                neighbors.emplace_back(make_pair(current.first - 1, current.second), "WN");
        }
        if(!southBorder && !westBorder && !world[(currentY + 1) * sideSize + (currentX - 1)]) // SE
            neighbors.emplace_back(make_pair(current.first - 1, current.second + 1), "SE");
        if(!southBorder && !world[(currentY + 1) * sideSize + (currentX)]) // SW
            neighbors.emplace_back(make_pair(current.first, current.second + 1), "SW");
    }

    return neighbors;
}

vector<pair<int, char>> Catcher::getDistances(pair<int,int> current, int sideSize)
{
    int size = sideSize / 2;
    vector<pair<int, char>> distances;
    distances.emplace_back(size + current.second, 'N'); // distance from north
    distances.emplace_back(size - current.second, 'S'); // distance from south
    distances.emplace_back(size - current.first, 'E'); // distance from east
    distances.emplace_back(size + current.first, 'W'); // distance from west
    // sort vector from smallest to biggest

    pair<int,char> holder;
    for(int i = 0; i < distances.size(); i++)
    {
        for(int j = i + 1; j < distances.size(); j++)
        {
            if(distances[i].first > distances[j].first)
            {
                holder = distances[i];
                distances[i] = distances[j];
                distances[j] = holder;
            }
        }
    }

    return distances;
}

bool Catcher::catWinsOnSpace(pair<int,int> pos, int sideSize)
{
    int size = sideSize / 2;
    if(pos.second >= size || pos.second <= -size)
    {
        return true;
    }
    else if(pos.first >= size || pos.first <= -size)
    {
        return true;
    }
    return false;
}

// used to hold cell data
struct Node
{
    pair<int,int> pos;
    int cost;
    int costToBorder;

    bool operator>(const Node& other) const
    {
        // used to order the priority queue by lowest cost
        return cost + costToBorder > other.cost + other.costToBorder;
    }
};


pair<int,int> Catcher::move(const vector<bool>& world, pair<int,int> catPos, int sideSize )
{
    pair<int,int> borderExit(100,100);

    priority_queue<Node, vector<Node>, greater<Node>> frontier; // puts nodes in a queue from low cost to high cost
    unordered_set< pair<int,int>, pairHash> frontierSet;
    unordered_map<pair<int,int>, pair<int,int>, pairHash> cameFrom;

    vector<pair<int, char>> initialDistance = getDistances(catPos, sideSize);
    Node origin;
    origin.pos = catPos;
    origin.cost = 0;
    origin.costToBorder = initialDistance[0].first;
    frontier.push(origin);
    cameFrom[catPos] = catPos;

    while (!frontier.empty())
    {
        Node current = frontier.top();
        frontier.pop();

        frontierSet.insert(current.pos);

        bool catWins = catWinsOnSpace(current.pos, sideSize);
        if (catWins)
        {
            borderExit = current.pos;
            break;
        }

        vector<pair<int, char>> distances = getDistances(current.pos,sideSize);
        vector<pair<pair<int,int>,string>> neighbors = getValidNeighbors(current.pos, world, sideSize, distances);

        for (auto it : neighbors)
        {
            if (frontierSet.find(it.first) == frontierSet.end()) // checks if neighbor is in frontierSet
            {
                int newCost = current.cost + 1; // costs 1 to move to next space

                int costToBorder;
                if(distances[it.second[0]].first < distances[it.second[1]].first) // check which direction of the neighbor is shortest
                {
                    costToBorder = distances[it.second[0]].first; // gets shortest distance of neighbor from border
                }
                else
                {
                    costToBorder = distances[it.second[1]].first;
                }

                // checks if neighbor is already in cameFrom and if the new cost is less than the current cost
                if (cameFrom.find(it.first) == cameFrom.end() || newCost + costToBorder < current.cost + current.costToBorder)
                {
                    Node newPath;
                    newPath.pos = it.first;
                    newPath.cost = newCost;
                    newPath.costToBorder = costToBorder;
                    frontier.push(newPath);
                    cameFrom[it.first] = current.pos;
                }
            }
        }
    }

    // no path was found
    if (borderExit == make_pair<int,int>(100,100))
    {
        return catPos;
    }

    // gets path from cameFrom
    vector<pair<int,int>> path;
    pair<int,int> current = borderExit;
    while (current != catPos)
    {

        path.push_back(current);
        current = cameFrom[current];
    }
    path.push_back(catPos);

    return path.front();
}