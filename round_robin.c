#include <stdio.h> //for printf

// Function to perform Round Robin scheduling with different arrival times
void roundRobin(int processes[], int n, int burst_time[], int arrival_time[], int quantum) {
    int remaining_time[n], turnaround_time[n], response_time[n]; //time left to run, TAT, and RT for each process
    int total_tat = 0, total_rt = 0; //running totals used to calculate averages
    int time = 0, completed = 0; //current clock time and how many processes have finished
    int first_response[n]; //the time each process first gets the CPU

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i]; //at the start, each process still needs its full burst time
        first_response[i] = -1;  // -1 means process hasn't started yet
    }

    // Continue until all processes are completed
    while (completed < n) {
        int all_waiting = 1;  //assume no process is ready until we find one

        //go through each process in order (one "round" of Round Robin)
        for (int i = 0; i < n; i++) {
            //only run a process if it still has work left AND has already arrived :p
            if (remaining_time[i] > 0 && arrival_time[i] <= time) {
                all_waiting = 0;  // At least one process is ready to execute

                //if this is the first time the process gets the CPU, record the time
                if (first_response[i] == -1) {
                    first_response[i] = time;
                }

                // Execute process for quantum or remaining time
                if (remaining_time[i] > quantum) {
                    //process needs more than one quantum: run for a full quantum, then move on
                    time += quantum; //advance the clock by one quantum
                    remaining_time[i] -= quantum; //subtract the time it just ran
                } else {
                    //process can finish within this quantum
                    time += remaining_time[i]; //advance the clock by only the time it needs
                    turnaround_time[i] = time - arrival_time[i]; //TAT = finish time - arrival time
                    remaining_time[i] = 0; //process has no work left
                    completed++; //one more process is done
                }
            }
        }

        // If all processes are waiting (not arrived yet), advance time
        if (all_waiting) {
            time++; //CPU is idle, so move the clock forward by 1
        }
    }

    // Print process details
    printf("Process\tBurst Time\tArrival Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = turnaround_time[i]; //TAT = finish time - arrival time
        response_time[i] = first_response[i] - arrival_time[i]; //RT = first time on CPU - arrival time

        //add this process's times to the totals
        total_tat += turnaround_time[i];
        total_rt += response_time[i];

        //print one row of the table for this process
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], arrival_time[i], turnaround_time[i], response_time[i]);
    }

    // Print average times (cast to float so the division keeps decimals)
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);
    printf("Average response time = %.2f\n", (float)total_rt / n);
}

int main() {
    //int processes[] = {1, 2, 3};  // Process IDs
    int processes[] = {1, 2, 3};
    //int burst_time[] = {40, 20, 10};  // Burst times for each process
    int burst_time[] = { 10, 5, 8 };
    //int arrival_time[] = {0, 0, 5};  // Arrival times for each process
    int arrival_time[] = { 0, 2, 4 };
    int n = sizeof(processes) / sizeof(processes[0]);  // Number of processes (total array size / size of one element)
    //int quantum = 5;  // Time quantum: max time a process runs before the next one gets a turn
    //int quantum = 1;
    //int quantum = 10;
    int quantum = 3; // used for comparison

    // Call Round Robin scheduling function
    roundRobin(processes, n, burst_time, arrival_time, quantum);

    return 0; 
}