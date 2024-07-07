#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "hr_agent.hpp"
#include "microbiologist.hpp"
#include "role.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

class environment {
  private:
    int amount_microbiologist;
    hr_agent* hr;
    std::vector<microbiologist> microbiologists;

    /**
     * @brief Create the microbiologists with their preferences
     * 
     */
    void create_microbiologists();
    /**
     * @brief Set the schedule for the human resources agent
     * 
     */
    void set_hr_schedule();

  public:
    /**
     * @brief Construct a new environment object
     * 
     * @param amount_microbiologist The amount of microbiologists to be represented 
     */
    environment(int amount_microbiologist);
    /**
     * @brief Destroy the environment object
     * 
     */
    ~environment();
    /**
     * @brief Calculate the fitness of a genome
     * 
     * @param genome The genome whose fitness will be calculated
     * @return double The fitness value
     */
    double fitness(std::vector<std::vector<int> >& genome);
    /**
     * @brief Create an initial population
     * 
     * @param size The size of the population
     * @param population The vector to store the population
     */
    void initial_population(int size, std::vector<role>& population);
    /**
     * @brief Print Monday and Friday
     * 
     */
    void print_weekdays();
};

#endif