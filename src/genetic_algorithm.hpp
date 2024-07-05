#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include "role.hpp"
#include "common.hpp"
#include "environment.hpp"

#include <iostream>
#include <vector>

class genetic_algorithm {
  private:
    std::vector<role> current_population;
    std::vector<role> new_population;
    std::vector<double> fitness;
    double global_fitness;
    environment * role_environment;

    void crossover();
    void mutate(int offspring1, int offspring2);
    void update_fitness(std::vector<role>& population);
    void show_population();
    void generate_parents(int& first_parent, int& second_parent);

  public:
    genetic_algorithm();
    ~genetic_algorithm();
    void run();
};

#endif