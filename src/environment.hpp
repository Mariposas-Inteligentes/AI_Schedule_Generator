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
    void create_microbiologists();
    void set_hr_schedule();

  public:
    environment(int amount_microbiologist);
    ~environment();
    double fitness(std::vector<std::vector<int> >& genome);
    void initial_population(int size, std::vector<role>& population);
    void print_weekdays();
};

#endif