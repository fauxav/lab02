#include <stdio.h>

//Function to calc turnaround time and response time using FIFO Scheduling with arrival times

void fifo(int processes[], int n, int burst_time[], int arrival_time[]) {
    int turnaround_time[n], response_time[n], completion_time[n]; //arrays for TAT, RT, and when each process finishes

    int total_tat = 0, total_rt = 0; //var for total turnaround time and total response times

    //First process starts as soon as it arrives
    response_time[0] = 0;
    completion_time[0] = arrival_time[0] + burst_time[0];
    turnaround_time[0] = completion_time[0] - arrival_time[0];

    //Add first process times to totals
    total_tat += turnaround_time[0];
    total_rt += response_time[0];

    //Calculate response and turnaround times for remaining processes
    for (int i = 1; i < n; i++) {
        int start_time = completion_time[i - 1]; //normally starts when prev process finishes
        if (arrival_time[i] > start_time)
            start_time = arrival_time[i]; //but if it hasn't arrived yet, CPU waits for it

        response_time[i] = start_time - arrival_time[i]; //RT = start - arrival
        completion_time[i] = start_time + burst_time[i]; //finishes after running its burst
        turnaround_time[i] = completion_time[i] - arrival_time[i]; //TAT = completion - arrival

        total_tat += turnaround_time[i]; //accumulate total TAT
        total_rt += response_time[i]; //accumulate total RT
    }

    //Display process details
    printf("Process\tArrival Time\tBurst Time\tTurnaround Time\tResponse Time\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], turnaround_time[i], response_time[i]);

    //Print average times
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
}

int main() {
    int processes[] = { 1, 2, 3 }; //process PIDs
    int burst_time[] = { 10, 5, 8 }; //Burst times for each PID
    int arrival_time[] = { 0, 2, 4 }; //Arrival times for each PID (must be in arrival order)
    int n = sizeof(processes) / sizeof(processes[0]); //num of processes. Also for counting contents of an array
    fifo(processes, n, burst_time, arrival_time); //call fifo function

    return 0;
}