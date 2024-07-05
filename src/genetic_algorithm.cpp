#include "genetic_algorithm.hpp"


genetic_algorithm::genetic_algorithm(): fitness(AMOUNT_POPULATION, 0.0) {
  this->role_environment = new environment(AMOUNT_MICRO);
  this->global_fitness = 0.0;
}

genetic_algorithm::~genetic_algorithm(){
  delete this->role_environment;  
}

void genetic_algorithm::update_fitness() {
  this->global_fitness = 0.0;
  for (int role = 0; role < AMOUNT_POPULATION; ++role) {
    this->fitness[role] = this->role_environment->fitness(this->current_population[role].get_genome());
    this->global_fitness += this->fitness[role];
  }
  this->global_fitness /= AMOUNT_POPULATION;
}

void genetic_algorithm::run(){
  // Generate initial population
  this->role_environment->initial_population(AMOUNT_POPULATION, this->current_population);

  // Calculate fitness of each chromosome

  while( true /*TODO(nosotros): criterio de satisfacción*/) {
    // TODO(nosotros): for de reproducir a todos
    
      // Select pair of chromosomes for mating

      // Crossover chromosomes

      // Mutate

      // Place new chromosomes in new_population
  }
  
  this->show_population();
}

void genetic_algorithm::crossover(){
  
}

void genetic_algorithm::mutate(){
  
}

void genetic_algorithm::show_population() {
  // TODO(nosotros): terminar
}
