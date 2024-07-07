#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include "role.hpp"
#include "common.hpp"
#include "environment.hpp"

#include <iostream>
#include <vector>
#include <algorithm>


class genetic_algorithm {
  private:
    std::vector<role> current_population;
    std::vector<role> new_population;
    std::vector<double> fitness;
    double global_fitness;
    double fitness_sum;
    environment * role_environment;

    /**
     * @brief Attempt a crossover between two parents
     * 
     */
    void crossover();
    /**
     * @brief Mutate two offstrings with several methods
     * 
     * @param offspring1 The first offspring to be mutated
     * @param offspring2 The second offspring to be mutated
     */
    void mutate(int offspring1, int offspring2);
    /**
     * @brief Update all variables related to the fitness
     * 
     * @param population The population to base off the fitness 
     */
    void update_fitness(std::vector<role>& population);
    /**
     * @brief Print the best members of a population
     * 
     */
    void show_population();
    /**
     * @brief Print the schedule for Mondays and Fridays
     * 
     */
    void show_schedule();
    /**
     * @brief Generate parents with a weighted probability
     * 
     * @param first_parent Stores the first parent
     * @param second_parent Stores the second parent
     */
    void generate_parents(int& first_parent, int& second_parent);
    void sort_population_by_fitness();

  public:
    /**
     * @brief Construct a new genetic algorithm object
     * 
     */
    genetic_algorithm();
    /**
     * @brief Destroy the genetic algorithm object
     * 
     */
    ~genetic_algorithm();
    void run();
};

#endif