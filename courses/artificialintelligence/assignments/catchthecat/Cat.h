#ifndef CAT_h
#define CAT_h
#include "IAgent.h"

struct Cat : public IAgent {
    std::vector<std::pair<std::pair<int,int>,std::string>> getValidNeighbors(const std::vector<bool>& world, std::pair<int,int> current, int sideSize)
    {
        int halfSideSize = sideSize / 2;
        std::vector<std::pair<std::pair<int,int>,std::string>> neighbors;
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
                neighbors.emplace_back(std::make_pair(current.first + 1, current.second - 1), "NE");
            if(!northBorder && !world[(currentY - 1) * sideSize + (currentX)]) // NW
                neighbors.emplace_back(std::make_pair(current.first, current.second - 1), "NW");
            if(!eastBorder && !world[(currentY) * sideSize + (currentX + 1)]) // E
                neighbors.emplace_back(std::make_pair(current.first + 1, current.second), "EE");
            if(!westBorder && !world[(currentY) * sideSize + (currentX - 1)]) // W
                neighbors.emplace_back(std::make_pair(current.first - 1, current.second), "WW");
            if(!southBorder && !world[(currentY + 1) * sideSize + (currentX)]) // SE
                neighbors.emplace_back(std::make_pair(current.first, current.second + 1), "SE");
            if(!southBorder && !eastBorder && !world[(currentY + 1) * sideSize + (currentX + 1)]) // SW
                neighbors.emplace_back(std::make_pair(current.first + 1, current.second + 1), "SW");
        }
        else
        {
            if(!northBorder && !world[(currentY - 1) * sideSize + (currentX)]) // NE
                neighbors.emplace_back(std::make_pair(current.first, current.second - 1), "NE");
            if(!northBorder && !westBorder && !world[(currentY - 1) * sideSize + (currentX - 1)]) // NW
                neighbors.emplace_back(std::make_pair(current.first - 1, current.second - 1), "NW");
            if(!eastBorder && !world[(currentY) * sideSize + (currentX + 1)]) // E
                neighbors.emplace_back(std::make_pair(current.first + 1, current.second), "EE");
            if(!westBorder && !world[(currentY) * sideSize + (currentX - 1)]) // W
                neighbors.emplace_back(std::make_pair(current.first - 1, current.second), "WW");
            if(!southBorder && !westBorder && !world[(currentY + 1) * sideSize + (currentX - 1)]) // SE
                neighbors.emplace_back(std::make_pair(current.first - 1, current.second + 1), "SE");
            if(!southBorder && !world[(currentY + 1) * sideSize + (currentX)]) // SW
                neighbors.emplace_back(std::make_pair(current.first, current.second + 1), "SW");
        }

        return neighbors;
    }
    std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{
        srand(time(nullptr));
        int size = sideSize / 2;
        std::vector<std::pair<int, char>> distances;
        distances.emplace_back(size + catPos.second, 'N'); // distance from north
        distances.emplace_back(size - catPos.second, 'S'); // distance from south
        distances.emplace_back(size - catPos.first, 'E'); // distance from east
        distances.emplace_back(size + catPos.first, 'W'); // distance from west
        std::pair<int,char> holder;

        // sort vector from smallest to biggest
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

        // gets all valid neighbor options
        std::vector<std::pair<std::pair<int,int>,std::string>> neighbors = getValidNeighbors(world,catPos,sideSize);

        if(neighbors.size() == 1)
              return neighbors.front().first;
        else if(neighbors.empty())
              return catPos;

        std::vector<std::pair<std::pair<int,int>,std::string>> holderVector = neighbors; // used to search through random neighbors

        int index = 0; // used to check the distances vector from smallest to largest
        int randIndex = 0;
        int randNum;
        while(true)
        {
            if(index >= distances.size())
                return catPos; // prevents infinite loop

            if (!holderVector.empty()) {
                if(holderVector.size() > 1)
                {
                    randNum = rand() % holderVector.size();
                    randIndex++;
                    if (randIndex > 99) {
                          randIndex = 0;
                    }
                }
                else
                    randNum = 0;

                if(randNum >= holderVector.size())
                    randNum = 0; // check to make sure it works

                // only moves in the direction of the random neighbor if its string matches the current index of distances
                if (distances[index].second == holderVector[randNum].second[0] || distances[index].second == holderVector[randNum].second[1]) {
                    return holderVector[randNum].first;
                }
                else {
                    std::swap(holderVector[randNum], holderVector.back()); // if direction doesn't fit swap the random with the back
                    holderVector.pop_back(); // remove the back vector
                }
            }
            else {
                holderVector = neighbors; // reset holderVector
                index++; // increases index to check for next closest distance
            }
        }
    }
};
#endif