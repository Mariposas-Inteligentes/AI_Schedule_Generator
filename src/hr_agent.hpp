#ifndef HR_AGENT
#define HR_AGENT

#include "common.hpp"
#include <cmath>
#include <numeric>
#include <vector>
#include <iostream>

class hr_agent {
  private:
    int amount_workers;
    std::vector<std::vector<std::vector<int> > > schedule;

    /**
     * @brief Calculates the fitness on a legal matter
     * 
     * @param genome The genome whose fitness will be calculated
     * @return double The fitness
     */
    double consult_legal(std::vector<std::vector<int> >& genome);
    /**
     * @brief Calculate the distribution of shifts among microbiologists
     * 
     * @param genome The genome whose fitness will be calculated
     * @return double The fitness
     */
    double consult_distribution(std::vector<std::vector<int> >& genome);
    /**
     * @brief Calculate the distribution between Saturdays and Sundays
     * 
     * @param genome The genome whose fitness will be calculated
     * @return double The fitness
     */
    double consult_weekend_dist(std::vector<std::vector<int> >& genome);
    /**
     * @brief Calculate the equality between microbiologists
     * 
    * @param genome The genome whose fitness will be calculated
     * @return double The fitness 
     */
    double consult_equality(std::vector<std::vector<int> >& genome);
    /**
     * @brief Check the pairings to see if it is illegal
     * 
     * @param genome The genome whose fitness will be calculated
     * @param week The week to be checked
     * @param day1 The first day
     * @param day2 The second day
     * @param fitness The fitness 
     */
    void check_pairing_week(std::vector<std::vector<int> >& genome
        , int week, int day1, int day2, double& fitness);
    /**
     * @brief Calculate the variance of a given array
     * 
     * @param numbers The numbers for the function
     * @return double The variance
     */
    double calculate_variance(std::vector<int> & numbers);

  public:
    /**
     * @brief Construct a new hr agent object
     * 
     * @param amount_workers The amount of microbiologists
     */
    hr_agent(int amount_workers);
    /**
     * @brief Destroy the hr agent object
     * 
     */
    ~hr_agent();
    /**
     * @brief Set the workers in schedule in a given week and day
     * 
     * @param week The week to be set
     * @param day The day to be set
     * @param workers The workers assigned to the week and day
     */
    void set_schedule(int week, int day, std::vector<int> workers);
    /**
     * @brief Calculate the fitness on a given genome
     * 
     * @param genome The genome whose fitness will be calculated
     * @return double The fitness
     */
    double fitness(std::vector<std::vector<int> > genome);
    /**
     * @brief Prints the schedule for Monday and Friday
     * 
     */
    void print_schedule();
};

#endif