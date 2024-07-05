#include "genetic_algorithm.hpp"


genetic_algorithm::genetic_algorithm(): fitness(AMOUNT_POPULATION, 0.0) {
  this->role_environment = new environment(AMOUNT_MICRO);
  this->global_fitness = 0.0;
}

genetic_algorithm::~genetic_algorithm(){
  delete this->role_environment;  
}

void genetic_algorithm::update_fitness(std::vector<role>& population) {
  this->global_fitness = 0.0;
  for (int role = 0; role < AMOUNT_POPULATION; ++role) {
    this->fitness[role] = this->role_environment->fitness(population[role].get_genome());
    this->global_fitness += this->fitness[role];
  }
  this->global_fitness /= AMOUNT_POPULATION;

  // TODO(lUIS): BORRAR
  std::cout << "global fitness: " << global_fitness << "\n";
}

void genetic_algorithm::run(){

  // TODO(lUIS): BORRAR
  std::cout << "Antes de generar initial population \n";

  // Generate initial population
  this->role_environment->initial_population(AMOUNT_POPULATION, this->current_population);

  std::cout << "Initial population: \n";
  this->show_population();

  // Calculate fitness of each chromosome
  this->update_fitness(this->current_population);

  while(this->global_fitness < STOP_CONDITION) {
    this->new_population.clear();
    // Crossover chromosomes and attempt to mutate them
    this->crossover();
    // Place new_population in current_population
    this->current_population = this->new_population;

    // Update fitness of current_popultion
    this->update_fitness(this->current_population);
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
        , this->new_population);
    this->mutate(i, i+1);
  }
}

void genetic_algorithm::generate_parents(int& first_parent, int& second_parent) {
  first_parent = 0;
  second_parent = 0;
  while (first_parent + second_parent <= this->global_fitness) {
    first_parent = rand() % AMOUNT_POPULATION;
    while (first_parent == second_parent) {
      second_parent = rand() % AMOUNT_POPULATION;
    }
  }
}

void genetic_algorithm::mutate(int offspring1, int offspring2) {
  this->new_population[offspring1].mutate();
  this->new_population[offspring2].mutate();
}

void genetic_algorithm::show_population() {
  this->sort_population_by_fitness(); 
  this->show_schedule();
  std::cout << "\n\n Weekends" << std::endl;
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

  std::sort(indices.begin(), indices.end(), [this](size_t a, size_t b) { return fitness[a] > fitness[b]; });

  std::vector<role> sorted_population;
  for (size_t i = 0; i < indices.size(); ++i) {
    sorted_population.push_back(this->current_population[indices[i]]);
  }
  this->current_population = std::move(sorted_population);
}