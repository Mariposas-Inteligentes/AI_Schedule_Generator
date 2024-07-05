#include "role.hpp"

role::role(int amount_micro): 
    genome(AMOUNT_WEEKS, std::vector<int>(AMOUNT_DAYS, -1)) {
  // row are weeks, columns are days
  this->amount_micro = amount_micro;
}

void role::create_random_genome() {
  for(int week = 0; week< AMOUNT_WEEKS; ++week) {
    for(int day = 0; day< AMOUNT_DAYS; ++day) {
      this->genome[week][day] = rand() % amount_micro; // [0, amount_micro[ 
    }
  }
}

role::~role() {
}

void role::crossover(role& dad, std::vector<role>& offsprings, int initial_pos) {
  // crossover probs
  int random = rand() % 101;
  int row_crossover = 0;
  int col_crossover = 0;
  if (random < PROBS_CROSSOVER) {
    row_crossover = rand() % AMOUNT_DAYS;
    col_crossover = rand() % AMOUNT_WEEKS;
    offsprings.push_back(role(this->amount_micro));
    offsprings.push_back(role(this->amount_micro));
    for (int row = 0; row < AMOUNT_WEEKS; ++row) {
      for (int col = 0; col < AMOUNT_DAYS; ++col) {
        if (row <= row_crossover && col <= col_crossover) {
          offsprings[initial_pos].write_genome(row, col, dad.genome[row][col]);
          offsprings[initial_pos+1].write_genome(row, col, this->genome[row][col]);
        } else {
          offsprings[initial_pos].write_genome(row, col, this->genome[row][col]);
          offsprings[initial_pos+1].write_genome(row, col, dad.genome[row][col]);
        }
      }
    }
  } else {  // clone
    offsprings.push_back(dad);
    offsprings.push_back(*this);
  }
}

void role::mutate() {
  int random = rand() % 101;
  if (random < PROBS_CROSSOVER) { // mutate
    int new_ids = rand() % (AMOUNT_DAYS * AMOUNT_WEEKS);
    int week = rand() % AMOUNT_WEEKS;
    int day = rand() % AMOUNT_DAYS;
    for (int i = 0; i < new_ids; ++i) {
      this->genome[week][day] = rand() % this->amount_micro;
      week = rand() % AMOUNT_WEEKS;
      day = rand() % AMOUNT_DAYS;
    }
  }
}

void role::write_genome(int row, int col, int value) {
  this->genome[row][col] = value;
}

std::vector<std::vector<int> >& role::get_genome() {
  return this->genome;
}

std::ostream& operator<<(std::ostream& os, const role& r) {
  os << "Sat Day\t\tSat Night\tSun Day\t\tSun Night\n";
  for(int week = 0; week< AMOUNT_WEEKS; ++week) {
    for(int day = 0; day< AMOUNT_DAYS; ++day) {
      os << r.genome[week][day] << "\t\t";
    }
    os << "\n";
  }
  return os;
}
