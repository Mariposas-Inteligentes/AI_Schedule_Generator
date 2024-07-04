#include "hr_agent.hpp"

hr_agent::hr_agent(int amount_workers)
    : amount_workers(amount_workers)
    , schedule(AMOUNT_WEEKS, std::vector<std::vector<int> >(2)){
}

hr_agent::~hr_agent(){
}

void hr_agent::set_schedule(int week, int day, std::vector<int> workers){
  this->schedule[week][day] = workers;
}

double hr_agent::fitness(std::vector<std::vector<int> > genome){
  double fitness = 0;

  fitness += 0.7 * this->consult_legal(genome);
  fitness += 0.1 * this->consult_distribution(genome);
  fitness += 0.1 * this->consult_weekend_dist(genome);
  fitness += 0.1 * this->consult_equality(genome);

  return fitness;
}

double hr_agent::consult_legal(std::vector<std::vector<int> > genome){
  double fitness = 5 * AMOUNT_WEEKS;  // there are 5 possible mistakes per week

  for (int week = 0; week < AMOUNT_WEEKS; ++week) {
    // Friday to Saturday morning
    this->check_pairing_week(genome, week, FRIDAY, SAT_DAY, fitness);

    // Saturday morning to Saturday night
    if (genome[week][SAT_DAY] == genome[week][SAT_NIGHT]) {
      --fitness;
    }
    
    // Saturday night to Sunday morning
    if (genome[week][SAT_NIGHT] == genome[week][SUN_DAY]) {
      --fitness;
    }
    
    // Sunday morning to Sunday night
    if (genome[week][SUN_DAY] == genome[week][SUN_NIGHT]) {
      --fitness;
    }
    
    // Sunday night to Monday
    this->check_pairing_week(genome, week, MONDAY, SUN_NIGHT, fitness);
  }

  return fitness;
}

void hr_agent::check_pairing_week(std::vector<std::vector<int> > genome
    , int week, int day1, int day2, double& fitness) {
  for (int micro = 0; micro < this->schedule[week][day1].size(); ++micro) {
    if (this->schedule[week][day1][micro] == genome[week][day2]) {
      --fitness;
    }
  }
}

double hr_agent::consult_distribution(std::vector<std::vector<int> > genome){
  std::vector<int> microbiologists_on_call(this->amount_workers, 0);

  for (int day = 0; day < AMOUNT_DAYS; ++day) {
    for (int week = 0; week < AMOUNT_WEEKS; ++week) {
      ++microbiologists_on_call[genome[day][week]];
    }
  }

  return this->calculate_variance(microbiologists_on_call);
}

double hr_agent::consult_weekend_dist(std::vector<std::vector<int> > genome){
  std::vector<int> microbiologists_income(this->amount_workers, 0);

  for (int week = 0; week < AMOUNT_WEEKS; ++week) {
    microbiologists_income[genome[SAT_DAY][week]] += 2;
    microbiologists_income[genome[SAT_NIGHT][week]] += 2;
    microbiologists_income[genome[SUN_DAY][week]] += 1;
    microbiologists_income[genome[SUN_NIGHT][week]] += 1;
  }

  return this->calculate_variance(microbiologists_income);
}

double hr_agent::consult_equality(std::vector<std::vector<int> > genome){
  std::vector<int> microbiologists_on_call(this->amount_workers, 0);
  int no_call = 0;
  double fitness = 0;

  for (int day = 0; day < AMOUNT_DAYS; ++day) {
    for (int week = 0; week < AMOUNT_WEEKS; ++week) {
      ++microbiologists_on_call[genome[day][week]];
    }
  }
  
  for (int micro = 0; micro < this->amount_workers; ++micro){
    if (microbiologists_on_call[micro] == 0) {
      ++no_call;
    }
  }

  if (this->amount_workers - no_call == AMOUNT_WEEKS * AMOUNT_DAYS) {
    fitness = 0;
  }

  return fitness;
}

double hr_agent::calculate_variance(std::vector<int> & numbers) {
  int size = numbers.size();
  double mean = std::accumulate(numbers.begin(), numbers.end(), 0.0) / size;
  double variance = 0.0;

  for (int i = 0; i < size; ++i) {
      variance += (numbers[i] - mean) * (numbers[i] - mean);
  }
  variance /= size;
  
  if (variance > 0.5) {
    variance = 0;
  } else {
    variance = 1;
  }
  
  return variance;
}