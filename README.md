---
title: TSP summariaze
tags: TSP,SA,ACO,TS
---
# TSP summariaze

:::spoiler 目錄
[TOC]
:::
## 1.	Using Simulated annealing algorithm (SA) .
        
(a)	Illustrate the strategy, Simulated annealing algorithm (SA)
        Simulated Annealing is an effective method to overcome the shortcomings of the hill climbing method, where the metallurgist repeatedly heats or cools the metal in order to achieve some specific crystal structure, and the control parameter of the process is the temperature T. The basic idea of Simulated Annealing is to allow the system to jump to the higher energy state occasionally during such a change in the system towards the trend of energy reduction. The basic idea of the simulated annealing method is to allow the system to occasionally jump to a higher energy state to avoid the local minima and eventually stabilize to the global minima.
        The key issues of the algorithm:

    - The setting of the initial and acceptance temperatures
    -	Local search method
    -	Annealing coefficient
    -	The number of internal cycles at a certain temperature
(b)	Design an algorithm to solve the problem with strategy in (a).
	Step 1: Initialization:
Given the variation range of each adoption number of the model, an initial solution is randomly selected within this range x, And calculate the objective function value of the response E ( x ). Set initial temperature T 0 , End temperature T f Generate random numbers ξ (0,1) As the probability threshold, set the cooling law.
	Step 2: At a certain temperature T Next, for the current solution 
x Perturb and produce a new solution c = x + △ x, Calculate the corresponding objective function value E(x′)versus  E(x)The difference, get△ E = E ( x ′ ) − E ( x ) 
	Step 3:If △ E < 0, The new solution x′ Be accepted if △ E > 0, 
	The new solution x′ By probability P = e x p ( − △ E / K ′ T ) been accepted, K ′Is a constant, usually 1; T Is the temperature. If P > ξ, then accept the new solution x′. When the solution x ′When accepted, set x=x′。
	Step 4: At temperature T Next, repeat the perturbation and 
acceptance process a certain number of times, that is, repeat steps 2 and 3.
      	Step 5: Slow down the temperature T。
        	Step 6: Repeat steps 2~5 until the convergence condition is met.
(c)	Write a program to implement your algorithm.
SA-TSP.cpp
city.txt

2.	Using genetic algorithm (GA) to solve the travelling salesman problem.
(a)	Illustrate the strategy, genetic algorithm (GA)
Core concept: Since the genetic algorithm is called genetic inheritance, the core concept is to first generate a random population and then select the most genetically superior individuals from it. These individuals are then allowed to reproduce and produce their offspring, and this process is repeated to ensure that the best genes are passed on.
(b)	Design an algorithm to solve the problem with strategy in (a).
i.	Initialize the population randomly.
ii.	. Determine the fitness of the chromosome.
iii.	. Until done repeat:
	. Select parents.
	. Perform crossover and mutation.
	. Calculate the fitness of the new population.
	. Append it to the gene pool.
(c)	Write a program to implement your algorithm.
GA_tsp.cpp
Solve Travelling Salesman Problem (TSP) by using Ant Colony Optimization (ACO)
	ACO:
	1) They choose the next path probabilistically. The probability is related to the length of the path and the concentration of pheromone on the path;
	2) In order to ensure that the logic of the solution is feasible, ants are not allowed to choose the path that has been taken;
	3) When ants walk along a path, they secrete a substance called pheromone on the path.
ACO-TSP.cpp



Solve Travelling Salesman Problem (TSP) by using Tabu search (TS)
TS:
Step 1:
 We first start with an initial solution s = S₀. This can be any solution that fits the criteria for an acceptable solution.
Step 2: 
 Generate a set of neighbouring solutions to the current solution s labeled N(s). From this set of solutions, the solutions that are in the Tabu List are removed with the exception of the solutions that fit the Aspiration Criteria. This new set of results is the new N(s).
s’ belongs to N(s)={ N(s)-T(s)}+A(s)
Step 3:
 Choose the best solution out of N(s) and label this new solution s’. If the solution s’ is better than the current best solution, update the current best solution. After, regardless if s’ is better than s, we update s to be s’.
Step 4:
 Update the Tabu List T(s) by removing all moves that are expired past the Tabu Tenure and add the new move s’ to the Tabu List. Additionally, update the set of solutions that fit the Aspiration Criteria A(s). If frequency memory is used, then also increment the frequency memory counter with the new solution.
Step 5:
 If the Termination Criteria are met, then the search stops or else it will move onto the next iteration. Termination Criteria is dependent upon the problem at hand but some possible examples are:
	a max number of iterations
	if the best solution found is better than some threshold
TS-TSP.cpp










Compare:
	First,compare them with time:follow by citys amount 20,31,51

 
Fig.1
According to fig1, we can see the time of Aco is twice of TS algorithm even 10 times of GA algorithm

Distance
 
Fig.2
As the distances, GA is the biggest one higher then others. 




Based on our simulation results we observed that:
1. GA algorithm take least time but get the biggest distance. So, it couldn’t be considered the optimal algorithm for solving TSP.
2. I thought ACO comes in the first order in finding the shortest
path, but it takes a long time in execution compared
to other algorithms. And the distance is similar to others, so it couldn’t be considered suitable algorithm. in finding optimal shortest
distance solution between cities.
3.GA comes in the first order in time execution (average< 1s)
And TS is both distance or time being second of all algorithms 
So, I think GA and TS should be considered suitable algorithm. in finding optimal shortest distance solution between cities.

ACO:
    
SA:
  
GA:
 
TS:
  

distance	aco	sa	ga	ts
20	251.5	243.17	255.9	257.33
31	304.36	320.6	331.59	328.97
51	449.8	441.25	518.8	442.782
Avg	335.22	335.0067	368.7633	343.0273
city:20city.txt					citys:31 	citys.txt		cities:51cities.txt
time	aco	sa	ga	ts
20	3.5	0.93	0.29	0.45
31	11.6	1.36	0.42	1.17
51	24.9	3.79	1.4	11.6
Avg	13.3	2.03	0.7	4.41






Time									Distance 
