#ifndef ROLE
#define ROLE

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

#include "common.hpp"

class role {
  friend std::ostream& operator<<(std::ostream& os, const role& r);

  private:
    std::vector<std::vector<int> > genome;
    int amount_micro;

    /**
     * @brief Write in a given row and column to the genome
     * 
     * @param row The row to be set
     * @param col The column to be set
     * @param value The value to be set
     */
    void write_genome(int row, int col, int value);

  public:
    /**
     * @brief Construct a new role object
     * 
     * @param amount_micro The amount of microbiologists
     */
    role(int amount_micro);
    /**
     * @brief Destroy the role object
     * 
     */
    ~role();
    /**
     * @brief Attemp to cross between the current object an a given dad
     * 
     * @param dad The dad to cross with
     * @param offsprings The offsprings from the cross
     * @param initial_pos The initial position
     */
    void crossover(role& dad, std::vector<role>& offsprings, int initial_pos);
    /**
     * @brief Attemp to mutate the current object's genome
     * 
     */
    void mutate();
    /**
     * @brief Create a random genome
     * 
     */
    void create_random_genome();
    /**
     * @brief Get the genome object
     * 
     * @return std::vector<std::vector<int> >& The genome to be returned
     */
    std::vector<std::vector<int> >& get_genome();
};

#endif