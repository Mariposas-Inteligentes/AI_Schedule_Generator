#ifndef MICROBIOLOGIST
#define MICROBIOLOGIST

#include "agent.hpp"

#include <vector>

#define SAT_DAY 0
#define SAT_NIGHT 1
#define SUN_DAY 2
#define SUN_NIGHT 3

#define AMOUNT_WEEKS 4
#define AMOUNT_DAYS 4

class microbiologist : agent {
  private:
    int id;
    std::vector<std::vector<char> > preferences;
    const static char WORKING = 'T';
    const static char NOT_WORKING = 'N';
    const static char VACATIONS = 'V';

  public:
    microbiologist(int id);
    microbiologist(int id, std::vector<std::vector<char> > preferences);
    ~microbiologist();
    int get_id();
    void set_id(int id);   
    void modify_preferences(int week, int day, char value);
    float look_at_role(std::vector<std::vector<int> > role);
};

#endif