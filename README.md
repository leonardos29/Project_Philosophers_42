# 🍝 Philosophers

*This project has been created as part of the 42 curriculum by [leonasil].*

---

## Description

**Philosophers** is a concurrency project from the 42 curriculum based on the classic **Dining Philosophers Problem**, originally formulated by Edsger Dijkstra in 1965.

The goal is to simulate a scenario where `N` philosophers sit around a circular table, alternating between three states: **eating**, **sleeping**, and **thinking**. Between each pair of adjacent philosophers lies a single fork — meaning a philosopher needs **two forks** (left and right) to eat.

The challenge is to manage shared resources (forks) using **mutexes** and **threads (pthreads)** to avoid:
- **Deadlocks** — where all philosophers wait indefinitely for a fork
- **Race conditions** — where concurrent access to shared data causes undefined behavior
- **Data races** — where threads read/write shared variables without synchronization
- **Starvation** — where a philosopher never gets to eat and dies

The simulation ends when a philosopher dies of starvation, or when all philosophers have eaten the required number of times (if specified).

---

## Instructions

### Compilation

```bash
make
```

This will compile the project and produce the `philo` executable. Other available rules:

```bash
make clean    # removes object files
make fclean   # removes object files and the executable
make re       # full recompile
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time in ms before a philosopher dies if they haven't eaten |
| `time_to_eat` | Time in ms it takes for a philosopher to eat |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(optional)* Simulation stops when all philosophers have eaten this many times |

All arguments must be positive integers.

### Usage Examples

```bash
# 5 philosophers, generous timing — no one should die
./philo 5 800 200 200

# 4 philosophers, tight timing — no one should die
./philo 4 410 200 200

# 1 philosopher — must die (only one fork available)
./philo 1 200 100 100

# 5 philosophers, must eat 7 times each then stop
./philo 5 800 200 200 7

# Tight case — expect a death
./philo 3 200 100 100
```

---

## Resources

### Documentation & References

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock(3) — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [pthread_create(3) — Linux man page](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [gettimeofday(2) — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### Articles & Tutorials

- [Mutex vs Semaphore — Baeldung](https://www.baeldung.com/cs/mutex-vs-semaphore)
- [Race Conditions and Mutexes — GeeksForGeeks](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
- [CodeVault — Threads playlist (YouTube)](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

### AI Usage

**Claude (Anthropic)** was used during this project for the following tasks:

- **Code review** — identifying potential race conditions, inconsistencies in mutex lock/unlock ordering, and edge cases (single philosopher, odd number of philosophers).
- **Debugging assistance** — analyzing simulation output to verify correctness of death detection timing and thread synchronization behavior.
- **README writing** — generating this document based on project requirements.

AI was **not** used to write the core logic of the project (thread creation, mutex management, philosopher routine, monitor).