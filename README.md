# Producer–Consumer Concurrency Simulation

**Academic C++ coursework | C++11 | POSIX threads | Semaphores | Mutexes**

A concurrent programming project demonstrating the classic producer–consumer problem using a bounded buffer. Six producers and four consumers coordinate access to a shared item count with POSIX semaphores and a mutex.

## Features

- Creates and joins worker threads using `pthread_create` and `pthread_join`.
- Uses `sem_wait` and `sem_post` to coordinate available capacity and items.
- Protects shared state using `pthread_mutex_lock` and `pthread_mutex_unlock`.
- Logs producer and consumer actions and the resulting shared item count.
- Joins the threads and releases synchronization resources before exiting.

## Build and run

Requires Linux or another POSIX-compatible environment, a C++ compiler, and `make`.

```bash
make
./producer-consumer
```

Alternatively, run `make run`. Run `make clean` to remove the executable.

The project was compiled with `g++ -std=c++11 -Wall -Wextra -pthread` and ran to completion on Linux. This does not constitute exhaustive concurrency testing.

## Files

- `src/producer_consumer.cpp` — implementation
- `Makefile` — build instructions
- `.gitignore` — excludes generated binaries and object files

## Background

Created as part of university computer science coursework in operating systems and concurrent programming.
