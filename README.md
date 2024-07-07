# Schedule Generator

## Problem

Scheduling medical personnel for weekend rotation is a problem that most health centers have to deal with. Every person has their preferences, and there are also policies that need to be followed when assigning people. This program aims to solve this problem for the case of microbiologists.

In the proposed problem, we have two shifts each day of the weekend, one from 6am to 6pm and the other one from 6pm to 6am. There has to be one microbiologist on each shift. Also, the program has access to the Friday night and Monday morning distribution.

Due to work policies:
1. No one is allowed to have two shifts in a row. 
2. There needs to be a similar distribution of shifts amongst them.
3. Since Saturday pays more than Sunday, there needs to be an even distribution of Saturdays and Sundays.
4. There needs to be at least one shift per microbiologist when the amount of microbiologist allows it.

The schedule must take into consideration 4 weekends of planning and it also must take into consideration the preferences of each microbiologist.

## Proposed solution:

To solve the problem, a genetic algorithm mixed with agents in `C++` was proposed. 

For this purpose, we have two types of agents: microbiologist and human resources (HR). There are several microbiologists in the environment, each one has a unique id and knows the preference of the microbiologist that it represents. Also, there is one HR agent, which is in charge of checking the four work policies. The algorithm crosses and mutates different schedule options until the global fitness reaches a defined stop condition. 

In order to calculate `fitness`, each agent will participate in a voting process where there is an assigned percentage to each opinion. 

This can be observed through the following formula (the parameters can be altered):

$$\text{fitness} = 0.8 \times \text{HRFitness}+0.2 \times\text{MicrobiologistsFitness}$$

Where `fitness` for the HR agent consists of how well each policy was followed:

$$\text{HRFitness} = 0.70\times \text{first policy} + 0.15\times \text{second policy} + 0.05\times \text{third policy} + 0.10\times \text{fourth policy}$$

And `fitness` for the microbiologists is an average of how well the desired schedules were followed:

$$\text{MicrobiologistsFitness}=\frac{\sum MicrobiologistFitness_n}{MicrobiologistAmount}$$

## Use

To compile, open a terminal in the project and execute:

```
g++ -o schedule src/main.cpp src/environment.cpp src/genetic_algorithm.cpp src/hr_agent.cpp  src/microbiologist.cpp src/role.cpp
```

To run, execute:

```
./schedule
```

## Requirements

The program was made to run in the operating system `Ubuntu 22`, so it is recommended to use this distribution to test it.

In order to change the parameters needed to run the genetic algorithm, you can modify the file [common.hpp](./src/common.hpp). And in order to modify the received preferences for each microbiologist, modify the file [microbiologists_weekend.txt](./files/microbiologists_weekends.txt). Where each line contains the preferences of one microbiologist for that month in the order: `Saturday morning`, `Saturday night`, `Sunday morning` and `Sunday night`. Each day can have 3 possible values:

1. `T`: Want to work
2. `N`: Do not want to work
3. `V`: On vacation before or after and don't want to work that weekend.

In order to modify the Friday night and Monday morning schedule you can change the file [microbiologists_workdays.txt](./files/microbiologists_workdays.txt). Where each line is a day, and the numbers are the ids assigned to each microbiologist on call on that shift. The lines alternate between Friday night, and Monday morning for each week. The numbers assigned must correspond to the ID of each microbiologist.

## Members
Luis David Solano Santamaría

Angie Sofía Solís Manzano

Emilia María Víquez Mora