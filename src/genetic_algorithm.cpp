#include "genetic_algorithm.hpp"


genetic_algorithm::genetic_algorithm(): fitness(AMOUNT_POPULATION, 0.0) {
  this->role_environment = new environment(AMOUNT_MICRO);
  this->global_fitness = 0.0;
}

genetic_algorithm::~genetic_algorithm(){
  delete this->role_environment;  
}

void genetic_algorithm::update_fitness(std::vector<role>& population) {
  this->fitness_sum = 0.0;
  for (int role = 0; role < AMOUNT_POPULATION; ++role) {
    this->fitness[role] = this->role_environment->fitness(population[role].get_genome());
    this->fitness_sum += this->fitness[role];
  }
  this->global_fitness = fitness_sum / AMOUNT_POPULATION;
}

void genetic_algorithm::run(){
  // Generate initial population and calculate fitness
  this->role_environment->initial_population(AMOUNT_POPULATION, this->current_population);
  this->update_fitness(this->current_population);
  this->sort_population_by_fitness();  

  std::cout << "Initial population: \n";
  this->show_population();

  std::cout << "\n\nCalculating final population... \n\n";

  int counter = 0;
  while(this->fitness[0] < STOP_CONDITION && counter < MAX_ITERATIONS) {
    std::cout << "Iteration " << counter++ << "___________________________\n";
    this->new_population.clear();
    // Crossover chromosomes and attempt to mutate them
    this->crossover();
    // Place new_population in current_population
    this->current_population = this->new_population;
    // Update fitness of current_popultion
    this->update_fitness(this->current_population);
    this->sort_population_by_fitness();
    // In case you want to see the evolution of the max fitness
    std::cout << "Best fitness of iteration: "<< this->fitness[0]<<"\n";
  }
  std::cout << "\n\nFinal population: \n";
  this->show_population();
}

void genetic_algorithm::crossover() {
  int parent1;
  int parent2;
  for (int i = 0; i < AMOUNT_POPULATION; i += 2) {
    this->generate_parents(parent1, parent2);
    this->current_population[parent1].crossover(this->current_population[parent2]
        , this->new_population, i);
    this->mutate(i, i+1);
  }
}

void genetic_algorithm::generate_parents(int& first_parent, int& second_parent) {
  double first_random = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / this->fitness_sum);
  double second_random = 0.0;
  // Generate the first parent
  for (int i = 0; i < AMOUNT_POPULATION; ++i) {
    if (first_random <= this->fitness[i]) {
      first_parent = i;
      break;
    }
    first_random -= this->fitness[i];
  }
  // Generate the second parent
  second_parent = first_parent;
  while (first_parent == second_parent) {
    second_random = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / this->fitness_sum);
    for (int i = 0; i < AMOUNT_POPULATION; ++i) {
      if (second_random <= this->fitness[i]) {
        second_parent = i;
        break;
      }
      second_random -= this->fitness[i];
    }
  }
}

void genetic_algorithm::mutate(int offspring1, int offspring2) {
  this->new_population[offspring1].mutate();
  this->new_population[offspring2].mutate();
}

void genetic_algorithm::show_population() {
  this->show_schedule();
  std::cout << "\n\nWeekends" << std::endl;
  for (int i = 0; i < PRINT_CHROMOSOMES; ++i) {
    std::cout << "\nRole " << i+1 << " - Fitness: " <<
        this->role_environment->fitness(this->current_population[i].get_genome()) <<std::endl;
    std::cout << this->current_population[i];
  }
}

void genetic_algorithm::show_schedule() {
  std::cout << "Week schedule: \n";
  this->role_environment->print_weekdays();
}

void genetic_algorithm::sort_population_by_fitness() {
  std::vector<size_t> indices(this->current_population.size());
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(), [this](size_t a, size_t b) { return this->fitness[a] > this->fitness[b]; });

  std::vector<role> sorted_population;
  std::vector<double> sorted_fitness;
  for (size_t i = 0; i < indices.size(); ++i) {
    sorted_population.push_back(this->current_population[indices[i]]);
    sorted_fitness.push_back(this->fitness[indices[i]]);
  }
  this->current_population = std::move(sorted_population);
  this->fitness = std::move(sorted_fitness);
}