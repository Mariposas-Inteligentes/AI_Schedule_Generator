#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "hr_agent.hpp"
#include "microbiologist.hpp"
#include <fstream>
#include <sstream>

class environment {
  private:
    int amount_microbiologist;
    hr_agent* hr;
    std::vector<microbiologist> microbiologists;

    std::vector<std::vector<char> > read_preferences();
    void create_microbiologists();

  public:
    environment(int amount_microbiologist);
    ~environment();
    double fitness(std::vector<std::vector<int> > genome);
};

#endif