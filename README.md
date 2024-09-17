# Philosophers
The Philosophers project is part of the 42 school curriculum and focuses on implementing the classic "Dining Philosophers Problem." It challenges developers to solve synchronization issues, handle multithreading,and avoid deadlocks in concurrent programming.

## About the Project
The Dining Philosophers Problem is a well-known problem in computer science that illustrates the issues of resource sharing and synchronization. In this project, multiple philosophers are seated at a table and must think and eat. However, each philosopher needs two forks to eat, and the forks are shared with their neighbors. The task is to ensure that the philosophers don’t starve (deadlock) or get stuck (livelock) while managing forks efficiently.

## Problem Description
- **N philosophers :** seated at a round table.
- Each philosopher can either be eating, thinking, or trying to pick up forks (to eat).
- Each philosopher needs two forks to eat: one from their left and one from their right.
- The goal is to prevent deadlocks and ensure proper synchronization while all philosophers eventually get their chance to eat.

## Key Concepts
- Concurrency
- Threads (one per philosopher)
- Mutexes (for fork management)
- Avoiding Deadlock by careful handling of resources

## Features
- **Multithreaded simulation:** Each philosopher is a separate thread.
- **Mutex-protected resource management:**  Forks are managed using mutexes to prevent race conditions.
- **Customizable parameters:** You can set the number of philosophers, time to eat, time to think, and time limits for each philosopher.
- **Deadlock avoidance mechanisms:** Implements strategies to avoid deadlocks (such as ordering fork pickups).

## Installation
1. **Clone the repository:**
   ```bash
   git clone https://github.com/amralkhaled221/philo.git
   cd philo
2. **Compile the project:**
   ```bash
   make
3. **Run :**
   ```bash
   ./philo 5 800 200 200
   
