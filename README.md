# AI_Schedule_Generator

## Members
Luis David Solano Santamaría
Angie Sofía Solís Manzano
Emilia María Víquez Mora

## Problem
Sheduling medical personale for weekend rotation is a problem that most healt centers have to deal with. Every person has their preferences, and there are also policies that need to be followed when asigning people. This program aims to solve this problem for the case of microbiologists.

In the proposed problem, we have two shifts each day of the weekend, one from 6am to 6pm and the other one from 6pm. There has to be one microbiologist on each shift. Also, the program has access to the Friday night and Monday morning distribution.

Due to hospital policies:
1. No one is allowed to have two shifts in a row. 
2. There needs to be a similar distribution of shifts amongst them.
3. Since Saturday pays more than Sunday, there needs to be an even distribution of Saturdays and Sundays.
4. There needs to be at least one shift per microbiologist when the amount of microbiologist allows it.

The schedule must take into consideration 4 weekends of planning and it also must take into consideration the preferences of each microbiologist.

## Proposed solution:
To solve the problem, a genetic algorithm was propposed. We have two types of agent: microbiologist and HR. There are several microbiologists in the environment, each one has a unique id and knows the preference of the microbiologist that it represents. Also, there is one HR agent, which is in charge of checking the four policies. The algorithm crosses and mutates different schedule options until the global fitness reaches a defined stop condition. 

In order to calculate fitness, the proportions are: 60%  fitness given by HR agent, and 40% average fitness given by all microbiologists.

Inside each microbiologist, fitness only considers if the desired schedule was met. Inside of the HR agent, fitness consits of 70% first policy, 10% second policy, 10% third policy and 10% the fourth policy. At the end, the total fitness for a schedule results in a number between 0 and 1. 

## Use

1. To compile, go to folder [src/](./src/) and type:

        g++ -o schedule *.cpp

2. To run, execute:

        ./schedule.out

The program was made to run in the operating system Ubuntu 22, so it is recomended to use this distribution to test it. In order to change the parameters needed to run the genetic algorithm, you can modify the file [common.hpp](./src/common.hpp). And in order to modify the received prefernces for each microbiologist, modify the file [microbiologists_weekend.txt](./src/microbiologists_weekends.txt). Where each line contains the prefferences of one microbiologist for that month in the order: `Saturday morning`, `Saturday night`, `Sunday morning` and `Sunday night`. Each day can have 3 possible values:

1. T: They want to work
2. N: They do not want to work
3. V: They are on vacation before or after and don't want to work that weekend.

To order to modify the Friday night and monday morning schedule you can change the file [microbiologists_workdays.txt](./src/microbiologists_workdays.txt). Where each line is a day, and the numbers are the ids asigned to each microbiologist on call on that shift. The lines alternate between Friday night, and Monday morning for each week. The numbers asigned must be from 0 to the amount of microbiologists minus one. 

