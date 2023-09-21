#include <iostream>
using namespace std;

int main(){
  unsigned int seed;
  unsigned int amount;
  signed int min;
  signed int max;

  unsigned int xorShift;
  int currentRandom;
  cin >> seed >> amount >> min >> max;

  for(int i = 0; i < amount; i++) {
      xorShift = seed << 13; // shift seed 13 bits to the left
      seed ^= xorShift; // xor of the original seed and the shifted seed
      xorShift = seed >> 17;
      seed ^= xorShift;
      xorShift = seed << 5;
      seed ^= xorShift;

      currentRandom = seed;
      currentRandom = min + (seed % (max - min + 1));

      cout << currentRandom << "\n";
  }
}