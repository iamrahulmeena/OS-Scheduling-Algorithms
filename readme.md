
# Operating System Scheduling Algorithms in C++

## Overview
This project implements seven popular CPU scheduling algorithms in C++ using Object-Oriented Programming (OOP) concepts. The goal is to simulate various scheduling strategies used by an operating system for managing process execution and optimize the process flow.

The algorithms implemented are:
1. **First-Come, First-Served (FCFS)**
2. **Shortest Job First (SJF)**
3. **Priority Scheduling**
4. **Round Robin (RR)**
5. **Shortest Remaining Time First (SRTF)**
6. **Multilevel Queue Scheduling**
7. **Multilevel Feedback Queue Scheduling**

### Key Features:
- **Modular Design**: Each algorithm is encapsulated into its own class, making it easy to extend or modify.
- **Optimized Implementation**: The code is optimized for better performance and readability, following best practices of OOP.
- **Polymorphism**: Uses polymorphism to allow scheduling algorithms to be easily substituted or extended.
- **Clear Results**: Displays waiting time and turnaround time for each process after the scheduling algorithm execution.

## Installation

### Prerequisites
- A C++ compiler (e.g., GCC, Clang)
- Basic knowledge of C++ and Operating System concepts

### Setup Instructions
1. Clone the repository or download the code files.
2. Open a terminal/command prompt.
3. Navigate to the directory where the code files are saved.
4. Compile the code using the following command:
   ```bash
   g++ -o scheduling main.cpp
   ```
5. Run the program:
   ```bash
   ./scheduling
   ```

## How to Use

1. Upon running the program, it will prompt you to enter the number of processes.
2. For each process, you will need to enter:
   - **Process ID**: A unique identifier for the process.
   - **Burst Time**: The amount of time the process requires to complete its execution.
   - **Arrival Time**: The time when the process arrives in the system.
   - **Priority (if applicable)**: The priority of the process (only for Priority-based scheduling).

3. You will also be prompted to enter the **Time Quantum** for algorithms like **Round Robin** and **Multilevel Feedback Queue**.

4. The program will execute all seven algorithms in sequence and display the results:
   - **Waiting Time**: The total time the process has been in the ready queue.
   - **Turnaround Time**: The total time taken from arrival to completion.

## Example Input

```text
Enter the number of processes: 3

Enter details for Process 1:
Process ID: 1
Burst Time: 10
Arrival Time: 0
Priority (0 if not applicable): 2

Enter details for Process 2:
Process ID: 2
Burst Time: 5
Arrival Time: 1
Priority (0 if not applicable): 1

Enter details for Process 3:
Process ID: 3
Burst Time: 8
Arrival Time: 2
Priority (0 if not applicable): 3

Enter Time Quantum for Round Robin and Multilevel Feedback Queue: 4
```

## Example Output

```text
FCFS Scheduling Results:
Process 1 - Waiting Time: 0, Turnaround Time: 10
Process 2 - Waiting Time: 9, Turnaround Time: 14
Process 3 - Waiting Time: 11, Turnaround Time: 19

SJF Scheduling Results:
Process 1 - Waiting Time: 9, Turnaround Time: 19
Process 2 - Waiting Time: 0, Turnaround Time: 5
Process 3 - Waiting Time: 5, Turnaround Time: 13

Priority Scheduling Results:
Process 1 - Waiting Time: 5, Turnaround Time: 15
Process 2 - Waiting Time: 0, Turnaround Time: 5
Process 3 - Waiting Time: 6, Turnaround Time: 14

Round Robin Scheduling Results:
Process 1 - Waiting Time: 4, Turnaround Time: 14
Process 2 - Waiting Time: 1, Turnaround Time: 6
Process 3 - Waiting Time: 4, Turnaround Time: 12

SRTF Scheduling Results:
Process 1 - Waiting Time: 0, Turnaround Time: 10
Process 2 - Waiting Time: 0, Turnaround Time: 5
Process 3 - Waiting Time: 3, Turnaround Time: 11

Multilevel Queue Scheduling Results:
Process 1 - Waiting Time: 0, Turnaround Time: 10
Process 2 - Waiting Time: 9, Turnaround Time: 14
Process 3 - Waiting Time: 11, Turnaround Time: 19

Multilevel Feedback Queue Scheduling Results:
Process 1 - Waiting Time: 0, Turnaround Time: 10
Process 2 - Waiting Time: 3, Turnaround Time: 8
Process 3 - Waiting Time: 6, Turnaround Time: 14
```

## Algorithms Implemented

### 1. **FCFS (First-Come, First-Served)**
- Executes processes in the order of their arrival time.
- Simple but inefficient as it may lead to long waiting times for processes with longer burst times.

### 2. **SJF (Shortest Job First)**
- Executes the shortest burst time first.
- Minimizes average waiting time but can cause starvation for longer processes.

### 3. **Priority Scheduling**
- Executes processes based on priority.
- Can be preemptive or non-preemptive depending on the system's implementation.

### 4. **Round Robin (RR)**
- Allocates a fixed time quantum to each process.
- Circulates through all processes, giving each a chance to execute within the time quantum.

### 5. **SRTF (Shortest Remaining Time First)**
- A preemptive version of SJF that selects the process with the shortest remaining burst time.

### 6. **Multilevel Queue Scheduling**
- Divides processes into different priority queues and schedules them accordingly.
- High priority processes are executed first, followed by lower priority processes.

### 7. **Multilevel Feedback Queue Scheduling**
- Similar to Multilevel Queue Scheduling but allows processes to move between queues based on their behavior (e.g., how long they take to execute).

## Contribution

Feel free to contribute to this project by:
- Adding new scheduling algorithms
- Improving performance
- Optimizing memory usage

## License

This project is open source and available under the [MIT License](LICENSE).
