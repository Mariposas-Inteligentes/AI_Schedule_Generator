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

## Example output
As you can see, the program prints the initial and final population along with the progress of the best role of each iteration for the user to see how it evolves. Given the nature of the program, since the fitness function involves the requests of all the microbiologists and the policies of the medical center, it is expected that the best solution achieved does not involve every agent being completely satisfied. We can see that the propposed schedule as the best solution found is legal, for there is no one with two shifts in a row and only two microbiologist do not have any assigned shift. Also, only one of them has two shifts (two sunday night shifts, which is part of the preferences of this worker). Overall, we can say that the algorithm produced a good solution solution. Here you can see the output given by the program:

```
Initial population: 
Week schedule: 
Week 1: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 13
		Microbiologist 15
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 3
		Microbiologist 4
		Microbiologist 7
		Microbiologist 10
		Microbiologist 12
		Microbiologist 14
		Microbiologist 15
Week 2: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 15
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 3
		Microbiologist 4
		Microbiologist 7
		Microbiologist 10
		Microbiologist 12
		Microbiologist 13
		Microbiologist 14
Week 3: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 13
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 3
		Microbiologist 4
		Microbiologist 7
		Microbiologist 10
		Microbiologist 12
		Microbiologist 14
Week 4: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 16
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 4
		Microbiologist 7
		Microbiologist 9
		Microbiologist 10
		Microbiologist 12
		Microbiologist 13
		Microbiologist 14


Weekends

Role 1 - Fitness: 0.685882
Sat Day		Sat Night	Sun Day		Sun Night
2		8		13		6		
4		5		15		16		
12		11		14		15		
9		3		6		11		

Role 2 - Fitness: 0.658618
Sat Day		Sat Night	Sun Day		Sun Night
9		15		10		0		
4		12		1		5		
14		3		11		6		
2		7		14		12		

Role 3 - Fitness: 0.657147
Sat Day		Sat Night	Sun Day		Sun Night
7		13		8		16		
4		10		1		16		
2		3		1		12		
15		9		4		11		

Role 4 - Fitness: 0.655676
Sat Day		Sat Night	Sun Day		Sun Night
7		1		10		16		
2		0		9		15		
0		14		6		8		
15		14		13		3		

Role 5 - Fitness: 0.655676
Sat Day		Sat Night	Sun Day		Sun Night
12		0		6		9		
5		7		8		16		
12		10		14		8		
13		0		3		11		


Calculating final population... 

Iteration 0___________________________
Best fitness of iteration: 0.684412
Iteration 1___________________________
Best fitness of iteration: 0.684412
Iteration 2___________________________
Best fitness of iteration: 0.657882
Iteration 3___________________________
Best fitness of iteration: 0.655676
Iteration 4___________________________
Best fitness of iteration: 0.656412
Iteration 5___________________________
Best fitness of iteration: 0.658618
Iteration 6___________________________
Best fitness of iteration: 0.657147
Iteration 7___________________________
Best fitness of iteration: 0.671353
Iteration 8___________________________
Best fitness of iteration: 0.684412
Iteration 9___________________________
Best fitness of iteration: 0.684412
Iteration 10___________________________
Best fitness of iteration: 0.656412
Iteration 11___________________________
Best fitness of iteration: 0.666206
Iteration 12___________________________
Best fitness of iteration: 0.656412
Iteration 13___________________________
Best fitness of iteration: 0.630618
Iteration 14___________________________
Best fitness of iteration: 0.629882
Iteration 15___________________________
Best fitness of iteration: 0.638206
Iteration 16___________________________
Best fitness of iteration: 0.656412
Iteration 17___________________________
Best fitness of iteration: 0.627676
Iteration 18___________________________
Best fitness of iteration: 0.631353
Iteration 19___________________________
Best fitness of iteration: 0.657147
Iteration 20___________________________
Best fitness of iteration: 0.656412
Iteration 21___________________________
Best fitness of iteration: 0.658618
Iteration 22___________________________
Best fitness of iteration: 0.656412
Iteration 23___________________________
Best fitness of iteration: 0.628412
Iteration 24___________________________
Best fitness of iteration: 0.632088
Iteration 25___________________________
Best fitness of iteration: 0.630618
Iteration 26___________________________
Best fitness of iteration: 0.631353
Iteration 27___________________________
Best fitness of iteration: 0.632088
Iteration 28___________________________
Best fitness of iteration: 0.660824
Iteration 29___________________________
Best fitness of iteration: 0.662294
Iteration 30___________________________
Best fitness of iteration: 0.658618
Iteration 31___________________________
Best fitness of iteration: 0.660824
Iteration 32___________________________
Best fitness of iteration: 0.660088
Iteration 33___________________________
Best fitness of iteration: 0.658618
Iteration 34___________________________
Best fitness of iteration: 0.669147
Iteration 35___________________________
Best fitness of iteration: 0.626941
Iteration 36___________________________
Best fitness of iteration: 0.603353
Iteration 37___________________________
Best fitness of iteration: 0.655676
Iteration 38___________________________
Best fitness of iteration: 0.651265
Iteration 39___________________________
Best fitness of iteration: 0.654941
Iteration 40___________________________
Best fitness of iteration: 0.685147
Iteration 41___________________________
Best fitness of iteration: 0.684412
Iteration 42___________________________
Best fitness of iteration: 0.660088
Iteration 43___________________________
Best fitness of iteration: 0.660088
Iteration 44___________________________
Best fitness of iteration: 0.687353
Iteration 45___________________________
Best fitness of iteration: 0.653471
Iteration 46___________________________
Best fitness of iteration: 0.660088
Iteration 47___________________________
Best fitness of iteration: 0.631353
Iteration 48___________________________
Best fitness of iteration: 0.660824
Iteration 49___________________________
Best fitness of iteration: 0.660824
Iteration 50___________________________
Best fitness of iteration: 0.659353
Iteration 51___________________________
Best fitness of iteration: 0.684412
Iteration 52___________________________
Best fitness of iteration: 0.655676
Iteration 53___________________________
Best fitness of iteration: 0.656412
Iteration 54___________________________
Best fitness of iteration: 0.655676
Iteration 55___________________________
Best fitness of iteration: 0.683676
Iteration 56___________________________
Best fitness of iteration: 0.631353
Iteration 57___________________________
Best fitness of iteration: 0.632088
Iteration 58___________________________
Best fitness of iteration: 0.624735
Iteration 59___________________________
Best fitness of iteration: 0.604824
Iteration 60___________________________
Best fitness of iteration: 0.658618
Iteration 61___________________________
Best fitness of iteration: 0.658618
Iteration 62___________________________
Best fitness of iteration: 0.657147
Iteration 63___________________________
Best fitness of iteration: 0.652735
Iteration 64___________________________
Best fitness of iteration: 0.657147
Iteration 65___________________________
Best fitness of iteration: 0.658618
Iteration 66___________________________
Best fitness of iteration: 0.659353
Iteration 67___________________________
Best fitness of iteration: 0.660824
Iteration 68___________________________
Best fitness of iteration: 0.682206
Iteration 69___________________________
Best fitness of iteration: 0.629147
Iteration 70___________________________
Best fitness of iteration: 0.631353
Iteration 71___________________________
Best fitness of iteration: 0.658618
Iteration 72___________________________
Best fitness of iteration: 0.657147
Iteration 73___________________________
Best fitness of iteration: 0.629147
Iteration 74___________________________
Best fitness of iteration: 0.657147
Iteration 75___________________________
Best fitness of iteration: 0.657147
Iteration 76___________________________
Best fitness of iteration: 0.631353
Iteration 77___________________________
Best fitness of iteration: 0.657147
Iteration 78___________________________
Best fitness of iteration: 0.657882
Iteration 79___________________________
Best fitness of iteration: 0.657147
Iteration 80___________________________
Best fitness of iteration: 0.682206
Iteration 81___________________________
Best fitness of iteration: 0.689559
Iteration 82___________________________
Best fitness of iteration: 0.657147
Iteration 83___________________________
Best fitness of iteration: 0.685882
Iteration 84___________________________
Best fitness of iteration: 0.655676
Iteration 85___________________________
Best fitness of iteration: 0.657882
Iteration 86___________________________
Best fitness of iteration: 0.657882
Iteration 87___________________________
Best fitness of iteration: 0.655676
Iteration 88___________________________
Best fitness of iteration: 0.656412
Iteration 89___________________________
Best fitness of iteration: 0.632824
Iteration 90___________________________
Best fitness of iteration: 0.659353
Iteration 91___________________________
Best fitness of iteration: 0.684412
Iteration 92___________________________
Best fitness of iteration: 0.685147
Iteration 93___________________________
Best fitness of iteration: 0.654206
Iteration 94___________________________
Best fitness of iteration: 0.658618
Iteration 95___________________________
Best fitness of iteration: 0.656412
Iteration 96___________________________
Best fitness of iteration: 0.657147
Iteration 97___________________________
Best fitness of iteration: 0.656412
Iteration 98___________________________
Best fitness of iteration: 0.632824
Iteration 99___________________________
Best fitness of iteration: 0.625471
Iteration 100___________________________
Best fitness of iteration: 0.655676
Iteration 101___________________________
Best fitness of iteration: 0.624735
Iteration 102___________________________
Best fitness of iteration: 0.629882
Iteration 103___________________________
Best fitness of iteration: 0.654206
Iteration 104___________________________
Best fitness of iteration: 0.657147
Iteration 105___________________________
Best fitness of iteration: 0.658618
Iteration 106___________________________
Best fitness of iteration: 0.660824
Iteration 107___________________________
Best fitness of iteration: 0.660088
Iteration 108___________________________
Best fitness of iteration: 0.660088
Iteration 109___________________________
Best fitness of iteration: 0.659353
Iteration 110___________________________
Best fitness of iteration: 0.658618
Iteration 111___________________________
Best fitness of iteration: 0.685882
Iteration 112___________________________
Best fitness of iteration: 0.688088
Iteration 113___________________________
Best fitness of iteration: 0.688088
Iteration 114___________________________
Best fitness of iteration: 0.685147
Iteration 115___________________________
Best fitness of iteration: 0.654206
Iteration 116___________________________
Best fitness of iteration: 0.681471
Iteration 117___________________________
Best fitness of iteration: 0.682206
Iteration 118___________________________
Best fitness of iteration: 0.680735
Iteration 119___________________________
Best fitness of iteration: 0.658618
Iteration 120___________________________
Best fitness of iteration: 0.654206
Iteration 121___________________________
Best fitness of iteration: 0.655676
Iteration 122___________________________
Best fitness of iteration: 0.629147
Iteration 123___________________________
Best fitness of iteration: 0.629147
Iteration 124___________________________
Best fitness of iteration: 0.629147
Iteration 125___________________________
Best fitness of iteration: 0.628412
Iteration 126___________________________
Best fitness of iteration: 0.629147
Iteration 127___________________________
Best fitness of iteration: 0.654941
Iteration 128___________________________
Best fitness of iteration: 0.683676
Iteration 129___________________________
Best fitness of iteration: 0.654941
Iteration 130___________________________
Best fitness of iteration: 0.657882
Iteration 131___________________________
Best fitness of iteration: 0.657882
Iteration 132___________________________
Best fitness of iteration: 0.658618
Iteration 133___________________________
Best fitness of iteration: 0.659353
Iteration 134___________________________
Best fitness of iteration: 0.631353
Iteration 135___________________________
Best fitness of iteration: 0.654941
Iteration 136___________________________
Best fitness of iteration: 0.657147
Iteration 137___________________________
Best fitness of iteration: 0.630618
Iteration 138___________________________
Best fitness of iteration: 0.681471
Iteration 139___________________________
Best fitness of iteration: 0.657882
Iteration 140___________________________
Best fitness of iteration: 0.628412
Iteration 141___________________________
Best fitness of iteration: 0.629882
Iteration 142___________________________
Best fitness of iteration: 0.654941
Iteration 143___________________________
Best fitness of iteration: 0.658618
Iteration 144___________________________
Best fitness of iteration: 0.656412
Iteration 145___________________________
Best fitness of iteration: 0.652735
Iteration 146___________________________
Best fitness of iteration: 0.655676
Iteration 147___________________________
Best fitness of iteration: 0.657882
Iteration 148___________________________
Best fitness of iteration: 0.682941
Iteration 149___________________________
Best fitness of iteration: 0.683676
Iteration 150___________________________
Best fitness of iteration: 0.682941
Iteration 151___________________________
Best fitness of iteration: 0.657147
Iteration 152___________________________
Best fitness of iteration: 0.658618
Iteration 153___________________________
Best fitness of iteration: 0.656412
Iteration 154___________________________
Best fitness of iteration: 0.656412
Iteration 155___________________________
Best fitness of iteration: 0.660088
Iteration 156___________________________
Best fitness of iteration: 0.660088
Iteration 157___________________________
Best fitness of iteration: 0.660824
Iteration 158___________________________
Best fitness of iteration: 0.657147
Iteration 159___________________________
Best fitness of iteration: 0.631353
Iteration 160___________________________
Best fitness of iteration: 0.656412
Iteration 161___________________________
Best fitness of iteration: 0.656412
Iteration 162___________________________
Best fitness of iteration: 0.654941
Iteration 163___________________________
Best fitness of iteration: 0.632088
Iteration 164___________________________
Best fitness of iteration: 0.683676
Iteration 165___________________________
Best fitness of iteration: 0.629882
Iteration 166___________________________
Best fitness of iteration: 0.631353
Iteration 167___________________________
Best fitness of iteration: 0.630618
Iteration 168___________________________
Best fitness of iteration: 0.656412
Iteration 169___________________________
Best fitness of iteration: 0.657882
Iteration 170___________________________
Best fitness of iteration: 0.660088
Iteration 171___________________________
Best fitness of iteration: 0.666206
Iteration 172___________________________
Best fitness of iteration: 0.655676
Iteration 173___________________________
Best fitness of iteration: 0.632088
Iteration 174___________________________
Best fitness of iteration: 0.656412
Iteration 175___________________________
Best fitness of iteration: 0.632824
Iteration 176___________________________
Best fitness of iteration: 0.660088
Iteration 177___________________________
Best fitness of iteration: 0.630618
Iteration 178___________________________
Best fitness of iteration: 0.629882
Iteration 179___________________________
Best fitness of iteration: 0.632088
Iteration 180___________________________
Best fitness of iteration: 0.655676
Iteration 181___________________________
Best fitness of iteration: 0.655676
Iteration 182___________________________
Best fitness of iteration: 0.657882
Iteration 183___________________________
Best fitness of iteration: 0.661559
Iteration 184___________________________
Best fitness of iteration: 0.661559
Iteration 185___________________________
Best fitness of iteration: 0.682941
Iteration 186___________________________
Best fitness of iteration: 0.657882
Iteration 187___________________________
Best fitness of iteration: 0.685147
Iteration 188___________________________
Best fitness of iteration: 0.644088
Iteration 189___________________________
Best fitness of iteration: 0.654206
Iteration 190___________________________
Best fitness of iteration: 0.657882
Iteration 191___________________________
Best fitness of iteration: 0.684412
Iteration 192___________________________
Best fitness of iteration: 0.657147
Iteration 193___________________________
Best fitness of iteration: 0.658618
Iteration 194___________________________
Best fitness of iteration: 0.659353
Iteration 195___________________________
Best fitness of iteration: 0.655676
Iteration 196___________________________
Best fitness of iteration: 0.656412
Iteration 197___________________________
Best fitness of iteration: 0.631353
Iteration 198___________________________
Best fitness of iteration: 0.657882
Iteration 199___________________________
Best fitness of iteration: 0.657882
Iteration 200___________________________
Best fitness of iteration: 0.685147
Iteration 201___________________________
Best fitness of iteration: 0.629147
Iteration 202___________________________
Best fitness of iteration: 0.656412
Iteration 203___________________________
Best fitness of iteration: 0.630618
Iteration 204___________________________
Best fitness of iteration: 0.626941
Iteration 205___________________________
Best fitness of iteration: 0.657147
Iteration 206___________________________
Best fitness of iteration: 0.657147
Iteration 207___________________________
Best fitness of iteration: 0.682206
Iteration 208___________________________
Best fitness of iteration: 0.632088
Iteration 209___________________________
Best fitness of iteration: 0.629147
Iteration 210___________________________
Best fitness of iteration: 0.659353
Iteration 211___________________________
Best fitness of iteration: 0.657147
Iteration 212___________________________
Best fitness of iteration: 0.657147
Iteration 213___________________________
Best fitness of iteration: 0.654941
Iteration 214___________________________
Best fitness of iteration: 0.657147
Iteration 215___________________________
Best fitness of iteration: 0.657147
Iteration 216___________________________
Best fitness of iteration: 0.657882
Iteration 217___________________________
Best fitness of iteration: 0.657882
Iteration 218___________________________
Best fitness of iteration: 0.657882
Iteration 219___________________________
Best fitness of iteration: 0.657882
Iteration 220___________________________
Best fitness of iteration: 0.685882
Iteration 221___________________________
Best fitness of iteration: 0.685882
Iteration 222___________________________
Best fitness of iteration: 0.655676
Iteration 223___________________________
Best fitness of iteration: 0.631353
Iteration 224___________________________
Best fitness of iteration: 0.626206
Iteration 225___________________________
Best fitness of iteration: 0.655676
Iteration 226___________________________
Best fitness of iteration: 0.682941
Iteration 227___________________________
Best fitness of iteration: 0.657882
Iteration 228___________________________
Best fitness of iteration: 0.655676
Iteration 229___________________________
Best fitness of iteration: 0.656412
Iteration 230___________________________
Best fitness of iteration: 0.682941
Iteration 231___________________________
Best fitness of iteration: 0.656412
Iteration 232___________________________
Best fitness of iteration: 0.658618
Iteration 233___________________________
Best fitness of iteration: 0.658618
Iteration 234___________________________
Best fitness of iteration: 0.632824
Iteration 235___________________________
Best fitness of iteration: 0.659353
Iteration 236___________________________
Best fitness of iteration: 0.657147
Iteration 237___________________________
Best fitness of iteration: 0.657882
Iteration 238___________________________
Best fitness of iteration: 0.630618
Iteration 239___________________________
Best fitness of iteration: 0.659353
Iteration 240___________________________
Best fitness of iteration: 0.629882
Iteration 241___________________________
Best fitness of iteration: 0.654941
Iteration 242___________________________
Best fitness of iteration: 0.630618
Iteration 243___________________________
Best fitness of iteration: 0.682206
Iteration 244___________________________
Best fitness of iteration: 0.682206
Iteration 245___________________________
Best fitness of iteration: 0.654206
Iteration 246___________________________
Best fitness of iteration: 0.657882
Iteration 247___________________________
Best fitness of iteration: 0.684412
Iteration 248___________________________
Best fitness of iteration: 0.682941
Iteration 249___________________________
Best fitness of iteration: 0.654206
Iteration 250___________________________
Best fitness of iteration: 0.653471
Iteration 251___________________________
Best fitness of iteration: 0.657147
Iteration 252___________________________
Best fitness of iteration: 0.660824
Iteration 253___________________________
Best fitness of iteration: 0.660824
Iteration 254___________________________
Best fitness of iteration: 0.657882
Iteration 255___________________________
Best fitness of iteration: 0.659353
Iteration 256___________________________
Best fitness of iteration: 0.632088
Iteration 257___________________________
Best fitness of iteration: 0.629882
Iteration 258___________________________
Best fitness of iteration: 0.680735
Iteration 259___________________________
Best fitness of iteration: 0.628412
Iteration 260___________________________
Best fitness of iteration: 0.628412
Iteration 261___________________________
Best fitness of iteration: 0.656412
Iteration 262___________________________
Best fitness of iteration: 0.631353
Iteration 263___________________________
Best fitness of iteration: 0.657147
Iteration 264___________________________
Best fitness of iteration: 0.659353
Iteration 265___________________________
Best fitness of iteration: 0.631353
Iteration 266___________________________
Best fitness of iteration: 0.654941
Iteration 267___________________________
Best fitness of iteration: 0.603353
Iteration 268___________________________
Best fitness of iteration: 0.685882
Iteration 269___________________________
Best fitness of iteration: 0.657147
Iteration 270___________________________
Best fitness of iteration: 0.658618
Iteration 271___________________________
Best fitness of iteration: 0.657147
Iteration 272___________________________
Best fitness of iteration: 0.657147
Iteration 273___________________________
Best fitness of iteration: 0.654941
Iteration 274___________________________
Best fitness of iteration: 0.657147
Iteration 275___________________________
Best fitness of iteration: 0.657147
Iteration 276___________________________
Best fitness of iteration: 0.659353
Iteration 277___________________________
Best fitness of iteration: 0.631353
Iteration 278___________________________
Best fitness of iteration: 0.629882
Iteration 279___________________________
Best fitness of iteration: 0.632824
Iteration 280___________________________
Best fitness of iteration: 0.658618
Iteration 281___________________________
Best fitness of iteration: 0.654941
Iteration 282___________________________
Best fitness of iteration: 0.657147
Iteration 283___________________________
Best fitness of iteration: 0.629147
Iteration 284___________________________
Best fitness of iteration: 0.659353
Iteration 285___________________________
Best fitness of iteration: 0.657147
Iteration 286___________________________
Best fitness of iteration: 0.656412
Iteration 287___________________________
Best fitness of iteration: 0.659353
Iteration 288___________________________
Best fitness of iteration: 0.632824
Iteration 289___________________________
Best fitness of iteration: 0.629147
Iteration 290___________________________
Best fitness of iteration: 0.629147
Iteration 291___________________________
Best fitness of iteration: 0.685147
Iteration 292___________________________
Best fitness of iteration: 0.654206
Iteration 293___________________________
Best fitness of iteration: 0.655676
Iteration 294___________________________
Best fitness of iteration: 0.657882
Iteration 295___________________________
Best fitness of iteration: 0.658618
Iteration 296___________________________
Best fitness of iteration: 0.660088
Iteration 297___________________________
Best fitness of iteration: 0.657882
Iteration 298___________________________
Best fitness of iteration: 0.657147
Iteration 299___________________________
Best fitness of iteration: 0.601882
Iteration 300___________________________
Best fitness of iteration: 0.655676
Iteration 301___________________________
Best fitness of iteration: 0.656412
Iteration 302___________________________
Best fitness of iteration: 0.629882
Iteration 303___________________________
Best fitness of iteration: 0.630618
Iteration 304___________________________
Best fitness of iteration: 0.682941
Iteration 305___________________________
Best fitness of iteration: 0.656412
Iteration 306___________________________
Best fitness of iteration: 0.601882
Iteration 307___________________________
Best fitness of iteration: 0.639676
Iteration 308___________________________
Best fitness of iteration: 0.659353
Iteration 309___________________________
Best fitness of iteration: 0.669882
Iteration 310___________________________
Best fitness of iteration: 0.683676
Iteration 311___________________________
Best fitness of iteration: 0.657147
Iteration 312___________________________
Best fitness of iteration: 0.682941
Iteration 313___________________________
Best fitness of iteration: 0.657882
Iteration 314___________________________
Best fitness of iteration: 0.685147
Iteration 315___________________________
Best fitness of iteration: 0.630618
Iteration 316___________________________
Best fitness of iteration: 0.688824
Iteration 317___________________________
Best fitness of iteration: 0.657147
Iteration 318___________________________
Best fitness of iteration: 0.657882
Iteration 319___________________________
Best fitness of iteration: 0.658618
Iteration 320___________________________
Best fitness of iteration: 0.657147
Iteration 321___________________________
Best fitness of iteration: 0.628412
Iteration 322___________________________
Best fitness of iteration: 0.630618
Iteration 323___________________________
Best fitness of iteration: 0.658618
Iteration 324___________________________
Best fitness of iteration: 0.659353
Iteration 325___________________________
Best fitness of iteration: 0.656412
Iteration 326___________________________
Best fitness of iteration: 0.654941
Iteration 327___________________________
Best fitness of iteration: 0.654941
Iteration 328___________________________
Best fitness of iteration: 0.652
Iteration 329___________________________
Best fitness of iteration: 0.656412
Iteration 330___________________________
Best fitness of iteration: 0.629882
Iteration 331___________________________
Best fitness of iteration: 0.657147
Iteration 332___________________________
Best fitness of iteration: 0.660824
Iteration 333___________________________
Best fitness of iteration: 0.658618
Iteration 334___________________________
Best fitness of iteration: 0.632088
Iteration 335___________________________
Best fitness of iteration: 0.657147
Iteration 336___________________________
Best fitness of iteration: 0.660088
Iteration 337___________________________
Best fitness of iteration: 0.658618
Iteration 338___________________________
Best fitness of iteration: 0.655676
Iteration 339___________________________
Best fitness of iteration: 0.630618
Iteration 340___________________________
Best fitness of iteration: 0.658618
Iteration 341___________________________
Best fitness of iteration: 0.654941
Iteration 342___________________________
Best fitness of iteration: 0.629882
Iteration 343___________________________
Best fitness of iteration: 0.629882
Iteration 344___________________________
Best fitness of iteration: 0.682206
Iteration 345___________________________
Best fitness of iteration: 0.68
Iteration 346___________________________
Best fitness of iteration: 0.654206
Iteration 347___________________________
Best fitness of iteration: 0.657147
Iteration 348___________________________
Best fitness of iteration: 0.657147
Iteration 349___________________________
Best fitness of iteration: 0.658618
Iteration 350___________________________
Best fitness of iteration: 0.660088
Iteration 351___________________________
Best fitness of iteration: 0.657882
Iteration 352___________________________
Best fitness of iteration: 0.695676
Iteration 353___________________________
Best fitness of iteration: 0.655676
Iteration 354___________________________
Best fitness of iteration: 0.683676
Iteration 355___________________________
Best fitness of iteration: 0.631353
Iteration 356___________________________
Best fitness of iteration: 0.655676
Iteration 357___________________________
Best fitness of iteration: 0.656412
Iteration 358___________________________
Best fitness of iteration: 0.656412
Iteration 359___________________________
Best fitness of iteration: 0.629882
Iteration 360___________________________
Best fitness of iteration: 0.657147
Iteration 361___________________________
Best fitness of iteration: 0.627676
Iteration 362___________________________
Best fitness of iteration: 0.627676
Iteration 363___________________________
Best fitness of iteration: 0.654206
Iteration 364___________________________
Best fitness of iteration: 0.627676
Iteration 365___________________________
Best fitness of iteration: 0.629147
Iteration 366___________________________
Best fitness of iteration: 0.659353
Iteration 367___________________________
Best fitness of iteration: 0.659353
Iteration 368___________________________
Best fitness of iteration: 0.654941
Iteration 369___________________________
Best fitness of iteration: 0.641147
Iteration 370___________________________
Best fitness of iteration: 0.682941
Iteration 371___________________________
Best fitness of iteration: 0.686618
Iteration 372___________________________
Best fitness of iteration: 0.686618
Iteration 373___________________________
Best fitness of iteration: 0.685882
Iteration 374___________________________
Best fitness of iteration: 0.684412
Iteration 375___________________________
Best fitness of iteration: 0.684412
Iteration 376___________________________
Best fitness of iteration: 0.633559
Iteration 377___________________________
Best fitness of iteration: 0.658618
Iteration 378___________________________
Best fitness of iteration: 0.657147
Iteration 379___________________________
Best fitness of iteration: 0.684412
Iteration 380___________________________
Best fitness of iteration: 0.657147
Iteration 381___________________________
Best fitness of iteration: 0.659353
Iteration 382___________________________
Best fitness of iteration: 0.602618
Iteration 383___________________________
Best fitness of iteration: 0.604088
Iteration 384___________________________
Best fitness of iteration: 0.684412
Iteration 385___________________________
Best fitness of iteration: 0.601882
Iteration 386___________________________
Best fitness of iteration: 0.629882
Iteration 387___________________________
Best fitness of iteration: 0.631353
Iteration 388___________________________
Best fitness of iteration: 0.628412
Iteration 389___________________________
Best fitness of iteration: 0.657882
Iteration 390___________________________
Best fitness of iteration: 0.657147
Iteration 391___________________________
Best fitness of iteration: 0.629882
Iteration 392___________________________
Best fitness of iteration: 0.685147
Iteration 393___________________________
Best fitness of iteration: 0.657882
Iteration 394___________________________
Best fitness of iteration: 0.630618
Iteration 395___________________________
Best fitness of iteration: 0.630618
Iteration 396___________________________
Best fitness of iteration: 0.632088
Iteration 397___________________________
Best fitness of iteration: 0.654941
Iteration 398___________________________
Best fitness of iteration: 0.657882
Iteration 399___________________________
Best fitness of iteration: 0.657882
Iteration 400___________________________
Best fitness of iteration: 0.685882
Iteration 401___________________________
Best fitness of iteration: 0.686618
Iteration 402___________________________
Best fitness of iteration: 0.684412
Iteration 403___________________________
Best fitness of iteration: 0.684412
Iteration 404___________________________
Best fitness of iteration: 0.655676
Iteration 405___________________________
Best fitness of iteration: 0.657882
Iteration 406___________________________
Best fitness of iteration: 0.671353
Iteration 407___________________________
Best fitness of iteration: 0.657882
Iteration 408___________________________
Best fitness of iteration: 0.655676
Iteration 409___________________________
Best fitness of iteration: 0.653471
Iteration 410___________________________
Best fitness of iteration: 0.656412
Iteration 411___________________________
Best fitness of iteration: 0.660088
Iteration 412___________________________
Best fitness of iteration: 0.654941
Iteration 413___________________________
Best fitness of iteration: 0.658618
Iteration 414___________________________
Best fitness of iteration: 0.655676
Iteration 415___________________________
Best fitness of iteration: 0.604088
Iteration 416___________________________
Best fitness of iteration: 0.685147
Iteration 417___________________________
Best fitness of iteration: 0.631353
Iteration 418___________________________
Best fitness of iteration: 0.632824
Iteration 419___________________________
Best fitness of iteration: 0.684412
Iteration 420___________________________
Best fitness of iteration: 0.644088
Iteration 421___________________________
Best fitness of iteration: 0.657882
Iteration 422___________________________
Best fitness of iteration: 0.659353
Iteration 423___________________________
Best fitness of iteration: 0.660824
Iteration 424___________________________
Best fitness of iteration: 0.654206
Iteration 425___________________________
Best fitness of iteration: 0.630618
Iteration 426___________________________
Best fitness of iteration: 0.657147
Iteration 427___________________________
Best fitness of iteration: 0.658618
Iteration 428___________________________
Best fitness of iteration: 0.657882
Iteration 429___________________________
Best fitness of iteration: 0.654206
Iteration 430___________________________
Best fitness of iteration: 0.629882
Iteration 431___________________________
Best fitness of iteration: 0.655676
Iteration 432___________________________
Best fitness of iteration: 0.631353
Iteration 433___________________________
Best fitness of iteration: 0.685147
Iteration 434___________________________
Best fitness of iteration: 0.629147
Iteration 435___________________________
Best fitness of iteration: 0.653471
Iteration 436___________________________
Best fitness of iteration: 0.630618
Iteration 437___________________________
Best fitness of iteration: 0.628412
Iteration 438___________________________
Best fitness of iteration: 0.629882
Iteration 439___________________________
Best fitness of iteration: 0.654206
Iteration 440___________________________
Best fitness of iteration: 0.657147
Iteration 441___________________________
Best fitness of iteration: 0.657147
Iteration 442___________________________
Best fitness of iteration: 0.655676
Iteration 443___________________________
Best fitness of iteration: 0.656412
Iteration 444___________________________
Best fitness of iteration: 0.657147
Iteration 445___________________________
Best fitness of iteration: 0.632088
Iteration 446___________________________
Best fitness of iteration: 0.630618
Iteration 447___________________________
Best fitness of iteration: 0.656412
Iteration 448___________________________
Best fitness of iteration: 0.658618
Iteration 449___________________________
Best fitness of iteration: 0.657882
Iteration 450___________________________
Best fitness of iteration: 0.629147
Iteration 451___________________________
Best fitness of iteration: 0.657147
Iteration 452___________________________
Best fitness of iteration: 0.630618
Iteration 453___________________________
Best fitness of iteration: 0.685882
Iteration 454___________________________
Best fitness of iteration: 0.682941
Iteration 455___________________________
Best fitness of iteration: 0.657882
Iteration 456___________________________
Best fitness of iteration: 0.685882
Iteration 457___________________________
Best fitness of iteration: 0.685147
Iteration 458___________________________
Best fitness of iteration: 0.686618
Iteration 459___________________________
Best fitness of iteration: 0.630618
Iteration 460___________________________
Best fitness of iteration: 0.657147
Iteration 461___________________________
Best fitness of iteration: 0.659353
Iteration 462___________________________
Best fitness of iteration: 0.657882
Iteration 463___________________________
Best fitness of iteration: 0.684412
Iteration 464___________________________
Best fitness of iteration: 0.682941
Iteration 465___________________________
Best fitness of iteration: 0.657882
Iteration 466___________________________
Best fitness of iteration: 0.658618
Iteration 467___________________________
Best fitness of iteration: 0.683676
Iteration 468___________________________
Best fitness of iteration: 0.659353
Iteration 469___________________________
Best fitness of iteration: 0.630618
Iteration 470___________________________
Best fitness of iteration: 0.657882
Iteration 471___________________________
Best fitness of iteration: 0.685147
Iteration 472___________________________
Best fitness of iteration: 0.629147
Iteration 473___________________________
Best fitness of iteration: 0.657147
Iteration 474___________________________
Best fitness of iteration: 0.652735
Iteration 475___________________________
Best fitness of iteration: 0.656412
Iteration 476___________________________
Best fitness of iteration: 0.630618
Iteration 477___________________________
Best fitness of iteration: 0.604088
Iteration 478___________________________
Best fitness of iteration: 0.631353
Iteration 479___________________________
Best fitness of iteration: 0.660824
Iteration 480___________________________
Best fitness of iteration: 0.657882
Iteration 481___________________________
Best fitness of iteration: 0.658618
Iteration 482___________________________
Best fitness of iteration: 0.653471
Iteration 483___________________________
Best fitness of iteration: 0.669882
Iteration 484___________________________
Best fitness of iteration: 0.633559
Iteration 485___________________________
Best fitness of iteration: 0.630618
Iteration 486___________________________
Best fitness of iteration: 0.685882
Iteration 487___________________________
Best fitness of iteration: 0.656412
Iteration 488___________________________
Best fitness of iteration: 0.655676
Iteration 489___________________________
Best fitness of iteration: 0.656412
Iteration 490___________________________
Best fitness of iteration: 0.656412
Iteration 491___________________________
Best fitness of iteration: 0.654206
Iteration 492___________________________
Best fitness of iteration: 0.631353
Iteration 493___________________________
Best fitness of iteration: 0.631353
Iteration 494___________________________
Best fitness of iteration: 0.630618
Iteration 495___________________________
Best fitness of iteration: 0.628412
Iteration 496___________________________
Best fitness of iteration: 0.656412
Iteration 497___________________________
Best fitness of iteration: 0.659353
Iteration 498___________________________
Best fitness of iteration: 0.657147
Iteration 499___________________________
Best fitness of iteration: 0.658618
Iteration 500___________________________
Best fitness of iteration: 0.657147
Iteration 501___________________________
Best fitness of iteration: 0.654941
Iteration 502___________________________
Best fitness of iteration: 0.657147
Iteration 503___________________________
Best fitness of iteration: 0.657147
Iteration 504___________________________
Best fitness of iteration: 0.630618
Iteration 505___________________________
Best fitness of iteration: 0.656412
Iteration 506___________________________
Best fitness of iteration: 0.657882
Iteration 507___________________________
Best fitness of iteration: 0.653471
Iteration 508___________________________
Best fitness of iteration: 0.656412
Iteration 509___________________________
Best fitness of iteration: 0.687353
Iteration 510___________________________
Best fitness of iteration: 0.659353
Iteration 511___________________________
Best fitness of iteration: 0.630618
Iteration 512___________________________
Best fitness of iteration: 0.631353
Iteration 513___________________________
Best fitness of iteration: 0.630618
Iteration 514___________________________
Best fitness of iteration: 0.657882
Iteration 515___________________________
Best fitness of iteration: 0.657147
Iteration 516___________________________
Best fitness of iteration: 0.657882
Iteration 517___________________________
Best fitness of iteration: 0.685882
Iteration 518___________________________
Best fitness of iteration: 0.683676
Iteration 519___________________________
Best fitness of iteration: 0.684412
Iteration 520___________________________
Best fitness of iteration: 0.687353
Iteration 521___________________________
Best fitness of iteration: 0.660088
Iteration 522___________________________
Best fitness of iteration: 0.659353
Iteration 523___________________________
Best fitness of iteration: 0.659353
Iteration 524___________________________
Best fitness of iteration: 0.657882
Iteration 525___________________________
Best fitness of iteration: 0.685147
Iteration 526___________________________
Best fitness of iteration: 0.628412
Iteration 527___________________________
Best fitness of iteration: 0.629147
Iteration 528___________________________
Best fitness of iteration: 0.629882
Iteration 529___________________________
Best fitness of iteration: 0.632824
Iteration 530___________________________
Best fitness of iteration: 0.656412
Iteration 531___________________________
Best fitness of iteration: 0.682206
Iteration 532___________________________
Best fitness of iteration: 0.657147
Iteration 533___________________________
Best fitness of iteration: 0.631353
Iteration 534___________________________
Best fitness of iteration: 0.657882
Iteration 535___________________________
Best fitness of iteration: 0.682206
Iteration 536___________________________
Best fitness of iteration: 0.684412
Iteration 537___________________________
Best fitness of iteration: 0.654941
Iteration 538___________________________
Best fitness of iteration: 0.657882
Iteration 539___________________________
Best fitness of iteration: 0.681471
Iteration 540___________________________
Best fitness of iteration: 0.681471
Iteration 541___________________________
Best fitness of iteration: 0.656412
Iteration 542___________________________
Best fitness of iteration: 0.656412
Iteration 543___________________________
Best fitness of iteration: 0.657147
Iteration 544___________________________
Best fitness of iteration: 0.632088
Iteration 545___________________________
Best fitness of iteration: 0.632088
Iteration 546___________________________
Best fitness of iteration: 0.632088
Iteration 547___________________________
Best fitness of iteration: 0.682206
Iteration 548___________________________
Best fitness of iteration: 0.657882
Iteration 549___________________________
Best fitness of iteration: 0.656412
Iteration 550___________________________
Best fitness of iteration: 0.656412
Iteration 551___________________________
Best fitness of iteration: 0.657147
Iteration 552___________________________
Best fitness of iteration: 0.657882
Iteration 553___________________________
Best fitness of iteration: 0.656412
Iteration 554___________________________
Best fitness of iteration: 0.631353
Iteration 555___________________________
Best fitness of iteration: 0.655676
Iteration 556___________________________
Best fitness of iteration: 0.659353
Iteration 557___________________________
Best fitness of iteration: 0.659353
Iteration 558___________________________
Best fitness of iteration: 0.658618
Iteration 559___________________________
Best fitness of iteration: 0.628412
Iteration 560___________________________
Best fitness of iteration: 0.661559
Iteration 561___________________________
Best fitness of iteration: 0.688088
Iteration 562___________________________
Best fitness of iteration: 0.657882
Iteration 563___________________________
Best fitness of iteration: 0.657147
Iteration 564___________________________
Best fitness of iteration: 0.603353
Iteration 565___________________________
Best fitness of iteration: 0.629882
Iteration 566___________________________
Best fitness of iteration: 0.630618
Iteration 567___________________________
Best fitness of iteration: 0.657147
Iteration 568___________________________
Best fitness of iteration: 0.669882
Iteration 569___________________________
Best fitness of iteration: 0.630618
Iteration 570___________________________
Best fitness of iteration: 0.660088
Iteration 571___________________________
Best fitness of iteration: 0.654941
Iteration 572___________________________
Best fitness of iteration: 0.634294
Iteration 573___________________________
Best fitness of iteration: 0.632824
Iteration 574___________________________
Best fitness of iteration: 0.660824
Iteration 575___________________________
Best fitness of iteration: 0.631353
Iteration 576___________________________
Best fitness of iteration: 0.661559
Iteration 577___________________________
Best fitness of iteration: 0.653471
Iteration 578___________________________
Best fitness of iteration: 0.657147
Iteration 579___________________________
Best fitness of iteration: 0.654206
Iteration 580___________________________
Best fitness of iteration: 0.656412
Iteration 581___________________________
Best fitness of iteration: 0.682941
Iteration 582___________________________
Best fitness of iteration: 0.683676
Iteration 583___________________________
Best fitness of iteration: 0.685882
Iteration 584___________________________
Best fitness of iteration: 0.685882
Iteration 585___________________________
Best fitness of iteration: 0.641147
Iteration 586___________________________
Best fitness of iteration: 0.682941
Iteration 587___________________________
Best fitness of iteration: 0.654206
Iteration 588___________________________
Best fitness of iteration: 0.656412
Iteration 589___________________________
Best fitness of iteration: 0.657882
Iteration 590___________________________
Best fitness of iteration: 0.655676
Iteration 591___________________________
Best fitness of iteration: 0.629882
Iteration 592___________________________
Best fitness of iteration: 0.655676
Iteration 593___________________________
Best fitness of iteration: 0.656412
Iteration 594___________________________
Best fitness of iteration: 0.684412
Iteration 595___________________________
Best fitness of iteration: 0.657882
Iteration 596___________________________
Best fitness of iteration: 0.657882
Iteration 597___________________________
Best fitness of iteration: 0.658618
Iteration 598___________________________
Best fitness of iteration: 0.685882
Iteration 599___________________________
Best fitness of iteration: 0.631353
Iteration 600___________________________
Best fitness of iteration: 0.654941
Iteration 601___________________________
Best fitness of iteration: 0.629147
Iteration 602___________________________
Best fitness of iteration: 0.629882
Iteration 603___________________________
Best fitness of iteration: 0.631353
Iteration 604___________________________
Best fitness of iteration: 0.633559
Iteration 605___________________________
Best fitness of iteration: 0.630618
Iteration 606___________________________
Best fitness of iteration: 0.656412
Iteration 607___________________________
Best fitness of iteration: 0.657882
Iteration 608___________________________
Best fitness of iteration: 0.657882
Iteration 609___________________________
Best fitness of iteration: 0.655676
Iteration 610___________________________
Best fitness of iteration: 0.660088
Iteration 611___________________________
Best fitness of iteration: 0.687353
Iteration 612___________________________
Best fitness of iteration: 0.660088
Iteration 613___________________________
Best fitness of iteration: 0.657147
Iteration 614___________________________
Best fitness of iteration: 0.655676
Iteration 615___________________________
Best fitness of iteration: 0.654206
Iteration 616___________________________
Best fitness of iteration: 0.684412
Iteration 617___________________________
Best fitness of iteration: 0.684412
Iteration 618___________________________
Best fitness of iteration: 0.684412
Iteration 619___________________________
Best fitness of iteration: 0.725147


Final population: 
Week schedule: 
Week 1: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 13
		Microbiologist 15
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 3
		Microbiologist 4
		Microbiologist 7
		Microbiologist 10
		Microbiologist 12
		Microbiologist 14
		Microbiologist 15
Week 2: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 15
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 3
		Microbiologist 4
		Microbiologist 7
		Microbiologist 10
		Microbiologist 12
		Microbiologist 13
		Microbiologist 14
Week 3: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 13
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 3
		Microbiologist 4
		Microbiologist 7
		Microbiologist 10
		Microbiologist 12
		Microbiologist 14
Week 4: 
	Friday night: 
		Microbiologist 0
		Microbiologist 1
		Microbiologist 3
		Microbiologist 5
		Microbiologist 6
		Microbiologist 8
		Microbiologist 11
		Microbiologist 16
	Monday morning: 
		Microbiologist 1
		Microbiologist 2
		Microbiologist 4
		Microbiologist 7
		Microbiologist 9
		Microbiologist 10
		Microbiologist 12
		Microbiologist 13
		Microbiologist 14


Weekends

Role 1 - Fitness: 0.725147
Sat Day		Sat Night	Sun Day		Sun Night
12		13		7		8		
9		16		15		0		
2		11		1		8		
10		4		5		6		

Role 2 - Fitness: 0.686618
Sat Day		Sat Night	Sun Day		Sun Night
12		14		13		11		
2		9		15		0		
2		12		16		5		
14		7		10		6		

Role 3 - Fitness: 0.655676
Sat Day		Sat Night	Sun Day		Sun Night
10		7		0		8		
14		9		12		2		
4		11		13		15		
9		11		16		0		

Role 4 - Fitness: 0.654941
Sat Day		Sat Night	Sun Day		Sun Night
14		8		0		5		
9		15		1		2		
10		11		3		15		
12		16		9		16		

Role 5 - Fitness: 0.630618
Sat Day		Sat Night	Sun Day		Sun Night
5		9		0		16		
15		11		3		8		
2		13		6		5		
14		12		8		6		

```


## Members
Luis David Solano Santamaría

Angie Sofía Solís Manzano

Emilia María Víquez Mora