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
    /**
     * @brief Construct a new microbiologist object
     * 
     * @param id 
     */
    microbiologist(int id);
    /**
     * @brief Construct a new microbiologist object
     * 
     * @param id The id for the worker
     * @param preferences The matrix of preferences
     */
    microbiologist(int id, std::vector<std::vector<char> > preferences);
    /**
     * @brief Destroy the microbiologist object
     * 
     */
    ~microbiologist();
    /**
     * @brief Get the id of the microbiologist
     * 
     * @return int The id
     */
    int get_id();
    /**
     * @brief Set the id
     * 
     * @param id The id to be set
     */
    void set_id(int id);
    /**
     * @brief Modify the preferences matrix on a given day and week
     * 
     * @param week The week to be changed
     * @param day The day to be changed
     * @param value The new value
     */
    void modify_preferences(int week, int day, char value);
    double fitness(std::vector<std::vector<int> > role);
};

#endif