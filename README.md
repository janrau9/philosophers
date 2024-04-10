Dining Philosophers Problem
Overview
The Dining Philosophers Problem is a classic synchronization problem in computer science,
which illustrates the challenges of resource allocation and deadlock avoidance in a concurrent system.
In this problem, a number of philosophers sit at a round table, and each philosopher alternates between thinking and eating. 
However, they must share a limited number of resources (forks) placed between them, leading to potential deadlocks if not properly managed.

This project aims to implement a solution to the Dining Philosophers Problem using Mutexes and Semaphores,
demonstrating various synchronization techniques to avoid deadlocks and ensure the safety of the philosophers.

Features
Philosopher Threads/forks: Each philosopher is represented by a thread/fork, which alternates eating, sleeping and thinkin.
Fork Management: Forks are shared resources that must be properly managed to avoid conflicts and deadlocks.
Each philosopher requires two forks to eat, one on their left and one on their right.
Deadlock Avoidance: Various synchronization mechanisms are employed to prevent deadlocks, such as mutex locks, semaphores, or other concurrency primitives.
Graceful Termination: The program gracefully terminates when all philosophers have finished their meals or when a termination condition is met.

arguments
1 number_of_philosophers: The number of philosophers and also the number
of forks.
2 time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
3 time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
4 time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
5 number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a

Example
$ ./philo 5 800 800 200 7

Simulation starts and all philosophers loops through it's own routine and exits when all have finished eating number of meals or if a philosopher died.
