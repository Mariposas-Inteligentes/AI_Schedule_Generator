#include "microbiologist.hpp"

microbiologist::microbiologist(int id) 
    : id(id), preferences(AMOUNT_WEEKS, std::vector<char>(AMOUNT_DAYS, NOT_WORKING)) {
}

microbiologist::microbiologist(int id, std::vector<std::vector<char> > preferences) 
: id(id), preferences(preferences) {
}

microbiologist::~microbiologist() {
}

int microbiologist::get_id() {
  return this->id;
}

void microbiologist::set_id(int id) {
  this->id = id;
} 
  
void microbiologist::modify_preferences(int week, int day, char value) {
  this->preferences[week][day] = value;
}

double microbiologist::fitness(std::vector<std::vector<int> > role) {
  double grade = 0;
  for (int week = 0; week < AMOUNT_WEEKS; ++week) {
    for (int day = 0; day < AMOUNT_DAYS; ++day) {
      if (role[week][day] == this->id) {  // have to work
        if (this->preferences[week][day] == WORKING) {
          ++grade; // If I wanted to work, it is good
        } else {
          if (this->preferences[week][day] == VACATIONS) {
            --grade; // If I was on vacation it is bad
          }
          // If I didn't want to work but was asigned to work, it does not affect much
        }
      }
    }
  }
  
  grade /= (AMOUNT_WEEKS*AMOUNT_DAYS); // [-1,1]

  return grade;
}
