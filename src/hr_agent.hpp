#ifndef HR_AGENT
#define HR_AGENT

#include "common.hpp"
#include <cmath>
#include <numeric>
#include <vector>

#include "agent.hpp"

class hr_agent : agent {
  private:
    int amount_workers;
    std::vector<std::vector<std::vector<int> > > schedule;

    double consult_legal(std::vector<std::vector<int> > genome);
    double consult_distribution(std::vector<std::vector<int> > genome);
    double consult_weekend_dist(std::vector<std::vector<int> > genome);
    double consult_equality(std::vector<std::vector<int> > genome);
    void check_pairing_week(std::vector<std::vector<int> > genome
        , int week, int day1, int day2, double& fitness);
    double calculate_variance(std::vector<int> & numbers);

  public: 
    hr_agent(int amount_workers);
    ~hr_agent();
    void set_schedule(int week, int day, std::vector<int> workers);
    double fitness(std::vector<std::vector<int> > genome);
};

#endif