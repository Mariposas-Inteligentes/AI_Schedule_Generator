#ifndef ROLE
#define ROLE

#include <vector>

class role {
  private:
    std::vector<std::vector<int>> genome;
  public:
    void mutate();
};

#endif