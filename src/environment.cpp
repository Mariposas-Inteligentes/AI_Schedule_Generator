#include "environment.hpp"

environment::environment(int amount_microbiologist)
    : amount_microbiologist(amount_microbiologist) {
  this->hr = new hr_agent(amount_microbiologist);
  this->create_microbiologists();
  this->set_hr_schedule();
}

environment::~environment() {
  delete this->hr;
}

double environment::fitness(std::vector<std::vector<int> >& genome) {
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

void environment::set_hr_schedule() {
  std::ifstream file("files/microbiologists_workdays.txt");
  if (!file.is_open()) {
    std::cerr << "Error opening weekdays file" << std::endl;
    return;
  }

  std::string line;
  int week = 0;
  int day = FRIDAY; 
  while (std::getline(file, line) && week < AMOUNT_WEEKS) {
    std::istringstream iss(line);
    std::vector<int> workers;
    int worker;
    
    while (iss >> worker) {
      workers.push_back(worker);
    }

    this->hr->set_schedule(week, day, workers);

    day = 1 - day; // Alternate between FRIDAY and MONDAY
    if (day == 0) { // when we are back to FRIDAY, add to week
      week++;
    }
  }

  file.close();
}

void environment::create_microbiologists() {
    std::ifstream file("files/microbiologists_weekends.txt");
    if (!file.is_open()) {
      std::cerr << "Error opening weekend file" << std::endl;
      return;
    }

    for (int i = 0; i < amount_microbiologist; ++i) {
      std::vector<std::vector<char>> preferences(AMOUNT_WEEKS, std::vector<char>(AMOUNT_DAYS));
      std::string line;
      std::getline(file, line);
      std::istringstream iss(line);
      for (int row = 0; row < AMOUNT_WEEKS; ++row) {
        for (int col = 0; col < AMOUNT_DAYS; ++col) {
          iss >> preferences[row][col];
        }
      }
      this->microbiologists.push_back(microbiologist(i, preferences));
    }
    file.close();
}



void environment::initial_population(int size, std::vector<role>& population) {
  population.clear();
  for(int i = 0; i < size; ++i) {
    population.push_back(role(this->amount_microbiologist));
    population[i].create_random_genome();
  }
}


void environment::print_weekdays() {
  this->hr->print_schedule();
}