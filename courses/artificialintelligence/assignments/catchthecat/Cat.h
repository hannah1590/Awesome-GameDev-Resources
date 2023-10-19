#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

struct Cat : public IAgent {
    pair<int,int> move(const vector<bool>& world, pair<int,int> catPos, int sideSize ) override;
};
#endif