#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Here I defined a structure to represent a process
struct Process {
    int priority;           // Priority of the process
    int burst_time;         // Remaining burst time of the process
    int turnaround_time;    // Turnaround time of the process
    int completion_time;    // Time when process is completed in the system
    int arrival_time;       // Arrival time of the process
};

// Here I defined a structure to represent a queue of processes

struct Queue {
    int priority_start;         // Lower bound of priority for the queue
    int priority_end;           // Upper bound of priority for the queue
    int completion_time;             // Total time spent by processes in the queue
    struct Process* processes;  // Array of processes in the queue
    int length;                 // Number of processes in the queue
    bool executed;              // Flag to track if the queue has been executed
};

// Function to check if any processes in the queues are incomplete (burst_time != 0)

bool isproc_incomplete(struct Queue* queues, int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        if (!queues[i].executed) {
            for (int j = 0; j < queues[i].length; j++) {
                if (queues[i].processes[j].burst_time != 0) {
                    return true;
                }
            }
            queues[i].executed = true;
        }
    }
    return false;
}

// Function to update the total time for processes in the queues

void upCompletionTime(struct Queue* queues, int num_queues) {
    for (int i = 0; i < num_queues; i++) {
        if (!queues[i].executed) {
            for (int j = 0; j < queues[i].length; j++) {
                if (queues[i].processes[j].burst_time != 0) {
                    queues[i].processes[j].completion_time += 1;
                }
            }
            queues[i].completion_time += 1;
        }
    }
}

// Function to sort a queue of processes by arrival time

void sortQueueByArrivalTime(struct Queue* queue) {
    int n = queue->length;
    struct Process* processes = queue->processes;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to sort a queue of processes by priority in descending order

void sortQueueByPriority(struct Queue* queue2) {
    int n = queue2->length;
    struct Process* processes = queue2->processes;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
//I made Main function here
int main() {
    printf("\nMulti-Level Queue Scheduler by Yash Mishra\n");
    printf("-------------------------------------------------------------------------------------\n\n");

    // Initialized an array of queues to categorize processes
    struct Queue queues[3];
    // Here I entered the priority ranges for the queues
    queues[0].priority_start = 1;
    queues[0].priority_end = 3;

    queues[0].length = 0;
    queues[0].completion_time = 0;
    queues[0].executed = false;

    queues[1].priority_start = 4;
    queues[1].priority_end = 6;
    queues[1].length = 0;
    queues[1].completion_time = 0;
    queues[1].executed = false;

    queues[2].priority_start = 7;
    queues[2].priority_end = 9;
    queues[2].length = 0;
    queues[2].completion_time = 0;
    queues[2].executed = false;

    int num_processes;
    // Here I asked the user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    struct Process all_procs[num_processes];

    // Input process details from the user
    for (int i = 0; i < num_processes; i++) {
        printf("Enter the priority of the process (from 1 to 9) Higher Number = Higher Priority: ");
        scanf("%d", &all_procs[i].priority);
        if(all_procs[i].priority<=0||all_procs[i].priority>9){
            printf("\nInvalid Priority selected. Scheduler will be exiting now.\n");
            printf("\nThank You for using Multi-Level Queue Scheduler\n");
            return 0;

        }
        
        printf("Enter the burst time of the process: ");
        scanf("%d", &all_procs[i].burst_time);
        if(all_procs[i].burst_time<0){
            printf("\nInvalid burst time entered. Scheduler will be exiting now.\n");
            printf("\nThank You for using Multi-Level Queue Scheduler\n");
            return 0;

        }
        if(i==0){
            all_procs[i].arrival_time=0;
        }
        else{
        printf("Enter the arrival time of the process: ");
        scanf("%d", &all_procs[i].arrival_time);
        }
        
        if(all_procs[i].arrival_time<0){
            printf("\nInvalid arrival time entered. Scheduler will be exiting now.\n");
            printf("\nThank You for using Multi-Level Queue Scheduler\n");
            return 0;

        }
        all_procs[i].turnaround_time = all_procs[i].burst_time;
        all_procs[i].completion_time = 0;
         // Here I selected the appropriate queue for the process based on its priority
        for (int j = 0; j < 3; j++) {
            if (queues[j].priority_start <= all_procs[i].priority && all_procs[i].priority <= queues[j].priority_end) {
                queues[j].length++;
            }
        }
    }
    // Allocated memory for each queue's processes based on their lengths using the malloc function
    for (int i = 0; i < 3; i++) {
        int len = queues[i].length;
        queues[i].processes = malloc(len * sizeof(struct Process));
    }

    int indexQueue0 = 0;
    int indexQueue1 = 0;
    int indexQueue2 = 0;
     // Separated processes into their respective queues
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < num_processes; j++) {
            if ((queues[i].priority_start <= all_procs[j].priority) && (all_procs[j].priority <= queues[i].priority_end)) {
                if (i == 0) {
                    queues[i].processes[indexQueue0++] = all_procs[j];
                } else if (i == 1) {
                    queues[i].processes[indexQueue1++] = all_procs[j];
                } else {
                    queues[i].processes[indexQueue2++] = all_procs[j];
                }
            }
        }
    }

    indexQueue0--;
    indexQueue1--;
    indexQueue2--;

    // Sorted the queues 1 and 3 by arrival time.
    sortQueueByArrivalTime(&queues[0]);
    sortQueueByArrivalTime(&queues[2]);

    // Sorted the second queue by priority in descending order.
    sortQueueByPriority(&queues[1]);

    // Initialize variables for scheduling and round robin.
    int timer = 0;
    int roundrobin_timer = 4;
    int counter = 0;
    int queueSelector = 0;
    
    // Start scheduling loop while there are incomplete processes
    while (isproc_incomplete(queues, 3)) {
        // Initialize timer for the current queue. When the timer reaches 10, the queue switches.
        timer = 0;
        // If the current queue has been executed, move to the next queue
        if (queues[queueSelector].executed) {
            queueSelector = (queueSelector + 1) % 3;
            continue;
        }

        // Perform scheduling for Queue 1-> Round Robin Algorithm
        /*Round Robin algo has 4 time quanta in queue 1. Once it gets to 0, it switched to other process in queue 1. There is also a timer which is 10 time quanta and switches queues
        based on Round-Robin. 
        Suppose the roundrobin_timer of queue 1 is at 2 and it gets switched to queue 2 due to 10 time quantas being finished then when it gets back to queue 1, it will be resumed from 2. 
        Suppose there is only one process in queue 1 then it will be executed as a whole till 10 time quantas are up, after which it will be shifted to the next queue.*/
        if (queueSelector == 0) {
            printf("Queue %d is being executed. Round-Robin Algorithm\n", queueSelector + 1);
            printf("-------------------------------------------------------------------------------------\n");
            if (roundrobin_timer == 0) {
                roundrobin_timer = 4;
            }

            for (int j = 0; j < queues[queueSelector].length; j++) {
        if (queues[queueSelector].processes[j].burst_time == 0) {
             counter++;
             continue;
        }

         if (counter == queues[queueSelector].length) {
             break;
        }

        // Count the number of processes with burst time greater than 0
        int remainingProcesses = 0;
        for (int k = 0; k < queues[queueSelector].length; k++) {
            if (queues[queueSelector].processes[k].burst_time > 0) {
                remainingProcesses++;
        }
        }

        // If there's only one process with burst time > 0, run it until timer reaches 10
        if (remainingProcesses == 1 && timer < 10) {
            while (queues[queueSelector].processes[j].burst_time > 0 && timer < 10) {
                printf("Process %d in Queue 1 is being executed for 1 unit time quanta. Process has priority of %d\n", j + 1, queues[queueSelector].processes[j].priority);
                queues[queueSelector].processes[j].burst_time--;
                upCompletionTime(queues, 3);
                roundrobin_timer--;
                timer++;
                }
            } 
            else {
            // Standard round-robin logic
            while (roundrobin_timer > 0 && queues[queueSelector].processes[j].burst_time != 0 && timer < 10) {
            printf("Process %d in Queue 1 is being executed for 1 unit time quanta. Process has priority of %d\n", j + 1, queues[queueSelector].processes[j].priority);
            queues[queueSelector].processes[j].burst_time--;
            upCompletionTime(queues, 3);
            roundrobin_timer--;
            timer++;
        }
    }

    if (timer == 10) {
        
        break;
    }

    if (queues[queueSelector].processes[j].burst_time == 0 && roundrobin_timer == 0) {
        roundrobin_timer = 4;
        if (j == (queues[queueSelector].length - 1)) {
            j = -1;
        }
        continue;
    }

    if (queues[queueSelector].processes[j].burst_time == 0 && roundrobin_timer > 0) {
        if (j == (queues[queueSelector].length - 1)) {
            j = -1;
        }
        continue;
    }

    if (roundrobin_timer <= 0) {
        roundrobin_timer = 4;
        if (j == (queues[queueSelector].length - 1)) {
            j = -1;
        }
         }
    }

        }
         // Perform scheduling for Queue 2->Priority based scheduling
        else if (queueSelector == 1) {
            printf("Queue %d is being executed. Priority Based Scheduling\n", queueSelector + 1);
            printf("-------------------------------------------------------------------------------------\n");
            for (int j = 0; j < queues[queueSelector].length; j++) {
                if (queues[queueSelector].processes[j].burst_time == 0) {
                    continue;
                }
                while (queues[queueSelector].processes[j].burst_time != 0 && timer != 10) {
                    printf("Process %d in Queue 2 is being executed for 1 unit time quanta. Process has priority of %d\n", j + 1, queues[queueSelector].processes[j].priority);
                    queues[queueSelector].processes[j].burst_time--;
                    upCompletionTime(queues, 3);
                    timer++;
                }

                if (timer == 10) {
                    break;
                }
            }
        } 
        // Perform scheduling for Queue 3-> First Come First Serve
        else {
            printf("Queue %d is being executed. First Come First Serve\n", queueSelector + 1);
            printf("-------------------------------------------------------------------------------------\n");
            for (int j = 0; j < queues[queueSelector].length; j++) {
                if (queues[queueSelector].processes[j].burst_time == 0) {
                    continue;
                }
                while (queues[queueSelector].processes[j].burst_time != 0 && timer != 10) {
                    printf("Process %d in Queue 3 is being executed for 1 unit time quanta. Process has priority of %d\n", j + 1, queues[queueSelector].processes[j].priority);
                    queues[queueSelector].processes[j].burst_time--;
                    upCompletionTime(queues, 3);
                    timer++;
                }

                if (timer == 10) {
                    break;
                }
            }
        }
        printf("Switching from Queue %d\n", (queueSelector + 1));
        printf("-------------------------------------------------------------------------------------\n\n");
        queueSelector = (queueSelector + 1) % 3;
    }
    // Calculate and display turnaround time and waiting time for each process
    float sum_turnaround_time = 0;
    float sum_waiting_time = 0;

    printf("\nProcess\t\tPriority\tArrival Time\tTurn Around Time\tWaiting Time");
    printf("\n-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < 3; i++) {
        printf("\nProcesses from Queue %d", i + 1);
        printf("\n-------------------------------------------------------------------------------------\n");
        for (int j = 0; j < queues[i].length; j++) {
            queues[i].processes[j].completion_time++;
            int turnaround_time = queues[i].processes[j].completion_time - queues[i].processes[j].arrival_time;
            int waiting_time = turnaround_time - queues[i].processes[j].turnaround_time;
            sum_turnaround_time += turnaround_time;
            sum_waiting_time += waiting_time;

            printf("P%d\t\t   %d\t\t      %d\t\t       %d\t\t      %d\n", j + 1, queues[i].processes[j].priority,queues[i].processes[j].arrival_time, turnaround_time , waiting_time);
        }
    }
    // Calculate and display average turnaround time and average waiting time
    printf("\nAverage Turnaround Time: %f seconds\n", sum_turnaround_time / num_processes);
    printf("Average Waiting Time: %f seconds\n", sum_waiting_time / num_processes);
    printf("\nThank You for using Multi-Level Queue Scheduler\n");

    return 0;
}
