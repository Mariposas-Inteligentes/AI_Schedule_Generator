#include "microbiologist.hpp"
#include "genetic_algorithm.hpp"

#include <cstdlib>
#include <ctime>

int main() {
  srand(time(NULL));

  genetic_algorithm algorithm;
  algorithm.run();

  return 0;
}