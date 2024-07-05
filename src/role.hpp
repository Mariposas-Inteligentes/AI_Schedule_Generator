#ifndef ROLE
#define ROLE

#include <vector>
#include <cstdlib>
#include <ctime>

#include "common.hpp"

class role {
  private:
    std::vector<std::vector<int> > genome;
    int amount_micro;

    void write_genome(int row, int col, int value);

  public:
    role(int amount_micro);
    ~role();
    std::vector<role> crossover(role& dad);
    void mutate();
    void create_random_genome();
};

#endif