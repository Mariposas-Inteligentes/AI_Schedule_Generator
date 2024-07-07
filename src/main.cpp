#include "microbiologist.hpp"
#include "genetic_algorithm.hpp"

#include <cstdlib>
#include <ctime>

void fitness() {
  environment env(17);  
  

  std::vector<std::vector<int> > genome;
  genome.push_back(std::vector<int>(4));
  genome.push_back(std::vector<int>(4));
  genome.push_back(std::vector<int>(4));
  genome.push_back(std::vector<int>(4));

  genome[0][SAT_DAY] = 2;
  genome[0][SAT_NIGHT] = 3;
  genome[0][SUN_DAY] = 1;
  genome[0][SUN_NIGHT] = 8;

  genome[1][SAT_DAY] = 4;
  genome[1][SAT_NIGHT] = 6;
  genome[1][SUN_DAY] = 15;
  genome[1][SUN_NIGHT] = 11;

  genome[2][SAT_DAY] = 7;
  genome[2][SAT_NIGHT] = 12;
  genome[2][SUN_DAY] = 10;
  genome[2][SUN_NIGHT] = 13;

  genome[3][SAT_DAY] = 14;
  genome[3][SAT_NIGHT] = 5;
  genome[3][SUN_DAY] = 9;
  genome[3][SUN_NIGHT] = 0;

  double fitness = env.fitness(genome);

  std::cout << "Result: " << fitness << std::endl;

}

int main() {
  //srand(time(NULL));
  srand(25);

  genetic_algorithm algorithm;
  algorithm.run();

  //fitness();

  return 0;
}