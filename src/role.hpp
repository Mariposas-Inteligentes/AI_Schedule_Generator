#ifndef ROLE
#define ROLE

#include <vector>

#define SAT_DAY 0
#define SAT_NIGHT 1
#define SUN_DAY 2
#define SUN_NIGHT 3

class role {
  private:
    std::vector<std::vector<int>> genome;
  public:
    void mutate();
};

#endif