#include "role.hpp"

role::role(int amount_micro): 
    genome(AMOUNT_WEEKS, std::vector<int>(AMOUNT_DAYS, -1)) {
  // row are weeks, columns are days
  this->amount_micro = amount_micro;
}

void role::create_random_genome() {
  for(int week = 0; week< AMOUNT_WEEKS; ++week) {
    for(int day = 0; day< AMOUNT_DAYS; ++day) {
      this->genome[week][day] = rand() % this->amount_micro; // [0, amount_micro[ 
    }
  }

  int micro = rand() % amount_micro;
  int week = rand() % AMOUNT_DAYS;
  int day = rand() % AMOUNT_WEEKS;
  for (int count = 0; count < this->amount_micro; ++count) {
    this->genome[week][day] = micro;
    ++micro;
    if (micro >= this->amount_micro) {
      micro = 0;
    }
    week = rand() % AMOUNT_DAYS;
    day = rand() % AMOUNT_WEEKS;
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
    int type_cross = rand() % 2;
    offsprings.push_back(role(this->amount_micro));
    offsprings.push_back(role(this->amount_micro));
    if (type_cross == 0) {
     row_crossover = rand() % AMOUNT_DAYS;
     col_crossover = rand() % AMOUNT_WEEKS;
      for (int row = 0; row < AMOUNT_WEEKS; ++row) {
        for (int col = 0; col < AMOUNT_DAYS; ++col) {
          if (row <= row_crossover && col <= col_crossover) {
            offsprings[offsprings.size()-2].write_genome(row, col, dad.genome[row][col]);
            offsprings[offsprings.size()-1].write_genome(row, col, this->genome[row][col]);
          } else {
            offsprings[offsprings.size()-2].write_genome(row, col, this->genome[row][col]);
            offsprings[offsprings.size()-1].write_genome(row, col, dad.genome[row][col]);
          }
        }
      }
    } else {
      int parent_chosen = rand() % 50;
      for (int row = 0; row < AMOUNT_WEEKS; ++row) {
        for (int col = 0; col < AMOUNT_DAYS; ++col) {
          // If the generated number is grater than the parent chosen, use the other parent
          if (parent_chosen <= (rand() % 100)) {
            offsprings[offsprings.size()-2].write_genome(row, col, dad.genome[row][col]);
            offsprings[offsprings.size()-1].write_genome(row, col, this->genome[row][col]);
          } else {
            offsprings[offsprings.size()-2].write_genome(row, col, this->genome[row][col]);
            offsprings[offsprings.size()-1].write_genome(row, col, dad.genome[row][col]);
          }
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
  while (random < PROBS_CROSSOVER) {
    int mutate_type = rand() % 3;
    int week = rand() % AMOUNT_WEEKS;
    int day = rand() % AMOUNT_DAYS;
    if (mutate_type == 0) {
      this->genome[week][day] = rand() % this->amount_micro;
    } else if (mutate_type == 1){
      int week2 = rand() % AMOUNT_WEEKS;
      int day2 = rand() % AMOUNT_DAYS;
      int temp = this->genome[week][day];
      this->genome[week][day] = this->genome[week2][day2];
      this->genome[week2][day2] = temp;
    } else {
      int week2 = week;
      while (week == week2) {
        week2 = rand() % AMOUNT_WEEKS;
      }
      for (int i = 0; i < AMOUNT_DAYS; ++i) {
        int temp = genome[week][i];
        genome[week][i] = genome[week2][i];
        genome[week2][i] = temp;
      }
    }
    
    random = rand() % 101;
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
