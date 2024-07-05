#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include "role.hpp"
#include "common.hpp"
#include "environment.hpp"
#include <vector>

class genetic_algorithm {
  private:
    std::vector<role> current_population;
    std::vector<role> new_population;
    std::vector<double> fitness;
    double global_fitness;
    environment * role_environment;

    void crossover();
    void mutate();
    void update_fitness();
    void show_population();

  public:
    genetic_algorithm();
    ~genetic_algorithm();
    void run();
};

#endif