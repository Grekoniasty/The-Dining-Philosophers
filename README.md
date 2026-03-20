# Philosophers

*This project has been created as part of the 42 curriculum by mpiasecz.*

## Description

A solution to the classic Dining Philosophers problem, implemented in C using POSIX threads and mutexes.

### The Problem

Five philosophers sit at a round table with a bowl of spaghetti. Between each pair of adjacent philosophers is a single fork. Each philosopher must alternately think and eat. However, a philosopher can only eat when they have both the left and right forks. After eating, they put down both forks and start thinking again.

The challenge is to design a concurrent algorithm that prevents deadlock (where all philosophers hold one fork and wait forever for another) and starvation (where a philosopher never gets to eat).

## Instructions

### Compilation

```bash
make
```

Other make rules:
- `make clean` — remove object files
- `make fclean` — remove object files and executable
- `make re` — recompile from scratch

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) at the table (1-250) |
| `time_to_die` | Time in ms a philosopher can survive without eating |
| `time_to_eat` | Time in ms it takes to eat (holding both forks) |
| `time_to_sleep` | Time in ms spent sleeping after eating |
| `meals_required` | Optional: simulation stops when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Same but stop after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# Edge case: single philosopher (will always die)
./philo 1 800 200 200
```

## Resources

### Documentation & References

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming - LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock(3) - Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday(2) - Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### Tutorials

- [Introduction to Threads - Neso Academy](https://www.youtube.com/watch?v=LOfGJcVnvAk)
- [Mutex in C - CodeVault](https://www.youtube.com/watch?v=oq29KUy29iQ)

### AI Usage

AI (Claude) was used to assist with:
- Explaining concurrency concepts during development
- Debugging race conditions and reviewing synchronization logic
- Explaining the idea of threads and usage of mutexes
