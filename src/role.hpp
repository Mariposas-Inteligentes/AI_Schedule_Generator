#ifndef ROLE
#define ROLE

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

#include "common.hpp"

class role {
  friend std::ostream& operator<<(std::ostream& os, const role& r);

  private:
    std::vector<std::vector<int> > genome;
    int amount_micro;

    void write_genome(int row, int col, int value);

  public:
    role(int amount_micro);
    ~role();
    void crossover(role& dad, std::vector<role>& offsprings, int initial_pos);
    void mutate();
    void create_random_genome();
    std::vector<std::vector<int> >& get_genome();
};

#endif