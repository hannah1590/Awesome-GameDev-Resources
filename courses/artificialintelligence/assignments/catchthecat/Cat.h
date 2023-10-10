#ifndef CAT_h
#define CAT_h
#include "IAgent.h"

struct Cat : public IAgent {

  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{
     std::vector<std::pair<int,int>> neighbors;
     int halfSideSize = sideSize / 2;

     // right / left
     if(catPos.first + 1 <= halfSideSize && !world[(catPos.second + halfSideSize) * sideSize + (catPos.first + 1 + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first + 1,catPos.second);
     }
     if(catPos.first - 1 >= -halfSideSize && !world[(catPos.second + halfSideSize) * sideSize + (catPos.first - 1 + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first - 1,catPos.second);
     }

     // upright
     if(catPos.second - 1 >= -halfSideSize && catPos.second % 2 == 0 && !world[(catPos.second - 1 + halfSideSize) * sideSize + (catPos.first + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first,catPos.second - 1);
     }
     if(catPos.first + 1 <= halfSideSize && catPos.second - 1 >= -halfSideSize && catPos.second % 2 == 1 && !world[(catPos.second - 1 + halfSideSize) * sideSize + (catPos.first + 1 + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first + 1,catPos.second - 1);
     }

     // upleft
     if(catPos.first - 1 >= -halfSideSize && catPos.second - 1 >= -halfSideSize && catPos.second % 2 == 0 && !world[(catPos.second - 1 + halfSideSize) * sideSize + (catPos.first - 1 + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first - 1,catPos.second - 1);
     }
     if(catPos.second - 1 >= -halfSideSize && catPos.second % 2 == 1 && !world[(catPos.second - 1 + halfSideSize) * sideSize + (catPos.first + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first,catPos.second - 1);
     }

     // downright
     if(catPos.second + 1 <= halfSideSize && catPos.second % 2 == 0 && !world[(catPos.second + 1 + halfSideSize) * sideSize + (catPos.first + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first,catPos.second + 1);
     }
     if(catPos.first + 1 <= halfSideSize && catPos.second + 1 <= halfSideSize && catPos.second % 2 == 1 && !world[(catPos.second + 1 + halfSideSize) * sideSize + (catPos.first + 1 + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first + 1,catPos.second + 1);
     }

     // downleft
     if(catPos.first - 1 >= -halfSideSize && catPos.second + 1 <= halfSideSize && catPos.second % 2 == 0 && !world[(catPos.second + 1 + halfSideSize) * sideSize + (catPos.first - 1 + halfSideSize)])
     {
         neighbors.emplace_back(catPos.first - 1,catPos.second + 1);
     }
      if(catPos.second + 1 <= halfSideSize && catPos.second % 2 == 1 && !world[(catPos.second + 1 + halfSideSize) * sideSize + (catPos.first + halfSideSize)])
      {
          neighbors.emplace_back(catPos.first,catPos.second + 1);
      }

      if(!neighbors.empty())
      {
          if(neighbors.size() == 1)
              return neighbors.back();
          else
          {
              srand(time(NULL));
              return neighbors[rand() % neighbors.size()];
          }
      }
      else
          return catPos;

  }
};
#endif