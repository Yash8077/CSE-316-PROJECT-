# **Multi-Level Queue Scheduling Algorithm Simulation**

## **Overview**
This project is a simulation of the **Multi-Level Queue Scheduling Algorithm**, implemented in **C programming language**. It demonstrates how processes are scheduled across multiple queues, each with its own scheduling algorithm and priority range. The program calculates **waiting time** and **turnaround time** for each process and provides an interactive way to understand CPU scheduling in operating systems.



## **Features**
- **Three Queues with Different Scheduling Algorithms**:
  1. **Queue 1**: Round Robin Scheduling (Time Quantum = 4 seconds).
  2. **Queue 2**: Priority Scheduling (Higher number = Higher priority).
  3. **Queue 3**: First Come First Serve (FCFS) Scheduling.

- **User Input**:
  - Enter the number of processes.
  - Input **priority**, **burst time**, and **arrival time** for each process.
  - Input validation for invalid priority, burst time, or arrival time.

- **Queue Switching**:
  - Each queue runs for a **Time Quantum of 10 seconds** before switching to the next queue.
  - Round Robin switches processes within its queue every **4 seconds**.

- **Output**:
  - Displays **turnaround time** and **waiting time** for each process.
  - Calculates and displays **average turnaround time** and **average waiting time**.



## **How It Works**
1. **Process Assignment**:
   - Processes are assigned to one of the three queues based on their priority:
     - **Queue 1**: Priority 7–9.
     - **Queue 2**: Priority 4–6.
     - **Queue 3**: Priority 1–3.

2. **Scheduling**:
   - Each queue executes its respective scheduling algorithm:
     - **Queue 1**: Round Robin (switches processes every 4 seconds).
     - **Queue 2**: Priority Scheduling (higher priority processes execute first).
     - **Queue 3**: FCFS (processes execute in the order of arrival).

3. **Queue Switching**:
   - After 10 seconds, the scheduler switches to the next queue.
   - If a queue has no processes or all processes are completed, it skips to the next queue.

4. **Completion**:
   - Once all processes are completed, the program calculates and displays:
     - Turnaround time and waiting time for each process.
     - Average turnaround time and average waiting time.



## **Code Structure**
- **Data Structures**:
  - `struct process`: Represents a process with attributes like `priority`, `burst_time`, `arrival_time`, `turnaround_time`, and `completion_time`.
  - `struct queue`: Represents a queue with attributes like `priority_range`, `processes`, `length`, and `executed`.

- **Functions**:
  - `is_proc_incomplete()`: Checks if any process in the queues is incomplete.
  - `update_completion_time()`: Updates the completion time for processes in a queue.
  - `sort_queue_by_arrival()`: Sorts processes in a queue by arrival time (for FCFS and Round Robin).
  - `sort_queue_by_priority()`: Sorts processes in a queue by priority (for Priority Scheduling).
  - `main()`: Handles user input, process assignment, scheduling, and output.



## **How to Run**
1. **Prerequisites**:
   - A C compiler (e.g., GCC).

2. **Steps**:
   - Clone the repository or download the source code.
   - Compile the program using GCC:
     ```bash
     gcc multi_level_queue_scheduler.c -o scheduler
     ```
   - Run the executable:
     ```bash
     ./scheduler
     ```

3. **Input**:
   - Enter the number of processes.
   - For each process, input:
     - Priority (1–9).
     - Burst time (positive integer).
     - Arrival time (non-negative integer).

4. **Output**:
   - The program will display:
     - The execution order of processes.
     - Turnaround time and waiting time for each process.
     - Average turnaround time and average waiting time.



## **Test Cases**
1. **Valid Input**:
   - Enter valid priority, burst time, and arrival time for processes.
   - Observe the scheduling and output.

2. **Invalid Input**:
   - Enter invalid priority (e.g., 10), burst time (e.g., -1), or arrival time (e.g., -1).
   - The program will detect invalid input and exit gracefully.

3. **Empty Queue**:
   - Test scenarios where one or more queues have no processes.
   - The program will skip empty queues and continue scheduling.



## **Example Output**
```
Multi-Level Queue Scheduler by Yash Mishra

Enter number of processes: 3
Enter priority, burst time, and arrival time for process 1: 8 5 0
Enter priority, burst time, and arrival time for process 2: 4 3 1
Enter priority, burst time, and arrival time for process 3: 2 6 2

Queue 1 (Round Robin) is being executed...
Process 1 (Priority 8) is being executed for 4 seconds.
Process 1 (Priority 8) is being executed for 1 second.
Queue 2 (Priority Scheduling) is being executed...
Process 2 (Priority 4) is being executed for 3 seconds.
Queue 3 (FCFS) is being executed...
Process 3 (Priority 2) is being executed for 6 seconds.

Process  Priority  Arrival Time  Turnaround Time  Waiting Time
1        8         0             5                0
2        4         1             4                1
3        2         2             8                2

Average Turnaround Time: 5.67
Average Waiting Time: 1.00

Thank you for using Multi-Level Queue Scheduler!
```



## **Contributing**
Contributions are welcome! If you find any issues or want to enhance the project, feel free to:
1. Fork the repository.
2. Create a new branch.
3. Submit a pull request.



## **License**
This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.



## **Acknowledgments**
- Inspired by operating system scheduling concepts.
- Special thanks to my mentors and peers for their guidance.



Enjoy exploring the world of CPU scheduling with this simulation! 🚀
