#include "environment.hpp"

environment::environment(int amount_microbiologist)
    : amount_microbiologist(amount_microbiologist) {
  this->hr = new hr_agent(amount_microbiologist);
  this->create_microbiologists();
}

environment::~environment() {
  delete this->hr;
}

double environment::fitness(std::vector<std::vector<int> > genome) {
  double fitness = 0;
  double micro_fitness = 0;

  fitness = 0.6 * this->hr->fitness(genome);
  
  for (int micro = 0; micro < this->amount_microbiologist; ++micro) {
    micro_fitness += this->microbiologists[micro].fitness(genome);
  }

  micro_fitness /= this->amount_microbiologist;
  fitness += 0.4 * micro_fitness;

  return fitness;
}


void environment::create_microbiologists() {
    std::ifstream file("./microbiologists.txt");
    if (!file.is_open()) {
      std::cerr << "Error opening file" << std::endl;
      return;
    }

    for (int i = 0; i < amount_microbiologist; ++i) {
      std::vector<std::vector<char>> preferences(4, std::vector<char>(6));
      std::string line;
      std::getline(file, line);
      std::istringstream iss(line);
      for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 6; ++col) {
          iss >> preferences[row][col];
        }
      }
      this->microbiologists.push_back(microbiologist(i, preferences));
    }
    file.close();
}

std::vector<role> environment::initial_population(int size) {
  std::vector<role> population;

  for(int i = 0; i < size; ++size) {
    population.push_back(role(this->amount_microbiologist));
    population[i].create_random_genome();
  }

  return population;
}
