#include <fstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

const std::string TEST_FOLDER = "\\tests\\";
unsigned int blumBlumShub(unsigned int seed, unsigned int r1, unsigned int r2);
bool isPrime(unsigned int n);

struct State {
  unsigned int seed;
  unsigned int r1;
  unsigned int r2;

  bool operator==(const State &other) const {
    return seed == other.seed && r1 == other.r1 && r2 == other.r2;
  }
};

namespace std {
  template <>
  struct hash<State> {
    size_t operator()(const State &s) const {
      return hash<unsigned int>()(s.seed) ^ hash<int>()(s.r1) ^ hash<int>()(s.r2);
    }
  };
}

int main() {
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;

  std::unordered_map<State, int> stateMap;
  unsigned int transientCount = 0, periodicPhase = 0;

  for (unsigned int i = N; i >= 1; i--) {
    State currentState = {seed, min, max};
    if (stateMap.count(currentState)) {
      transientCount = stateMap[currentState];
      periodicPhase = i - transientCount;
      break;
    }
    stateMap[currentState] = i;
    seed = blumBlumShub(seed, min, max);
    std::cout << seed << std::endl;
  }

  std::cout << "Transient Count: " << transientCount << std::endl;
  std::cout << "Periodic Phase: " << periodicPhase << std::endl;
}

unsigned int blumBlumShub(unsigned int seed, unsigned int r1, unsigned int r2)
{
  //The line below adds additional checks to make outcomes more random, but isn't completely necessary
  //if(r1 % 4 == 3 && r2 % 4 == 3 && isPrime(r1) && isPrime(r2) && isPrime(r1 / 2) && isPrime(r2) / 2)
    return (seed * seed) % (r1 * r2);
}

bool isPrime(unsigned int n)
{
  if (n <= 1) return false;

  for (unsigned int i = 2; i < n; i++)
  {
    if (n % i == 0) return false;
  }

  return true;
}
