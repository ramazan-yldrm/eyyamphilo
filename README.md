*This project has been created as part of the 42 curriculum by ryildiri.*

# Philosophers

> *I never thought philosophy would be so deadly.*

## Description

**Philosophers** is a 42 School project that introduces the fundamentals of concurrent programming through the classic **Dining Philosophers Problem**, originally formulated by Edsger Dijkstra.

A number of philosophers sit around a round table with a large bowl of spaghetti in the middle. There are as many forks as philosophers — one between each pair. To eat, a philosopher must pick up both the fork to their left and the fork to their right. After eating, they put the forks down and go to sleep. After sleeping, they think. The simulation ends when a philosopher dies of starvation — or, optionally, when every philosopher has eaten a set number of times.

The goal is to implement this simulation without any deadlocks, data races, or starvation — keeping all philosophers alive.

The mandatory part uses **threads** and **mutexes**. The bonus part uses **processes** and **semaphores**.

---

## Instructions

### Requirements

- GCC or Clang
- POSIX-compatible OS (Linux / macOS)
- `make`

### Compilation

**Mandatory part:**
```bash
cd philo
make
```

**Bonus part:**
```bash
cd philo_bonus
make
```

### Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time before a philosopher dies if they haven't started eating |
| `time_to_eat` (ms) | Time it takes for a philosopher to eat (holds 2 forks) |
| `time_to_sleep` (ms) | Time a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, should not die
./philo 5 800 200 200

# 4 philosophers, must eat 7 times each
./philo 4 410 200 200 7

# 1 philosopher — will always die (only one fork)
./philo 1 800 200 200
```

### Log Format

Every state change is printed as:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

Messages never overlap, and a death message is printed within 10 ms of the actual event.

---

## Technical Notes

- No global variables are used anywhere in the project.
- Each philosopher is a separate **thread** (mandatory) or **process** (bonus).
- Each fork is protected by a **mutex** (mandatory) or represented by a **semaphore** (bonus).
- The program is free of data races (verified with `valgrind --tool=helgrind` and `ThreadSanitizer`).
- All heap-allocated memory is properly freed before exit.

---

## Resources

### Documentation & References

- [POSIX Threads Programming – Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [The Dining Philosophers Problem – Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [`pthread_mutex_lock` man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [`sem_overview` man page](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
- [`gettimeofday` man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Data Races and How to Avoid Them – cppreference](https://en.cppreference.com/w/c/language/memory_model)

### AI Usage

AI (Claude) was used in the following ways during this project:

- **Conceptual clarification:** Asking for plain-language explanations of mutex locking strategies and deadlock prevention techniques, then verifying the answers against official documentation and peer discussion.
- **Debugging assistance:** Describing unexpected behavior (e.g., occasional deaths under tight timing) and using AI suggestions as a starting point for investigation — always confirmed and understood before applying.
- **README drafting:** The initial structure of this README was generated with AI assistance and then reviewed, corrected, and expanded manually.

All AI-generated content was reviewed, tested, and fully understood before being included in the project.