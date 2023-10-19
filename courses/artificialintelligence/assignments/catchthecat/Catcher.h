#ifndef CATCHER_H
#define CATCHER_H
#include "IAgent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

struct Catcher : public IAgent {
    pair<int,int> move(const vector<bool>& world, pair<int,int> catPos, int sideSize ) override;
};
#endif