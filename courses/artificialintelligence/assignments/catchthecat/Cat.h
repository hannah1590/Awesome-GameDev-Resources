#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

struct Cat : public IAgent {
    vector<pair<pair<int,int>,string>> getValidNeighbors(pair<int,int> current, const vector<bool>& world, int sideSize, vector<pair<int, char>>& distances);
    vector<pair<int, char>> getDistances(pair<int,int> current, int sideSize);
    bool catWinsOnSpace(pair<int,int> pos, int sideSize);
    pair<int,int> move(const vector<bool>& world, pair<int,int> catPos, int sideSize ) override;
};
#endif