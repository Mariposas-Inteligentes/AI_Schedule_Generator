#ifndef MICROBIOLOGIST
#define MICROBIOLOGIST

#include "common.hpp"
#include <vector>

class microbiologist {
  private:
    int id;
    std::vector<std::vector<char> > preferences;
    const char WORKING = 'T';
    const char NOT_WORKING = 'N';
    const char VACATIONS = 'V';

  public:
    microbiologist(int id);
    microbiologist(int id, std::vector<std::vector<char> > preferences);
    ~microbiologist();
    int get_id();
    void set_id(int id);   
    void modify_preferences(int week, int day, char value);
    double fitness(std::vector<std::vector<int> > role);
};

#endif