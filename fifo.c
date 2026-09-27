#include <stdio.h>

//Function to calc turnaround time and response time using FIFO Scheduling

void fifo(int processes[], int n, int burst_time[]) {
    int turnaround_time[n], response_time[n]; //arrays for turnaround time and response time

    int total_tat = 0, total_rt = 0; //var for total turnaround time and total response times

    //First process starts immediately
    response_time[0] = 0;
    turnaround_time[0] = burst_time[0];

    //Add first process times to totals
    total_tat += turnaround_time[0];
    total_rt += response_time[0];

    //Calculate response and turnaround times for remaining processes
    for (int i = 1; i < n; i++) {
        response_time[i] = response_time[i - 1] + burst_time[i - 1]; //response time is the sum of prev burst times
        turnaround_time[i] = response_time[i] + burst_time[i]; //TAT = response + burst

        total_tat += turnaround_time[i]; //accumulate total TAT
        total_rt += response_time[i]; //accumulate total RT
    }

    //Display process details
    printf("Process\tBurst Time\tTurnaround Time\tResponse Time\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], turnaround_time[i], response_time[i]);

    //Print average times
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
}

int main() {
    int processes[] = { 1, 2, 3}; //process PIDs
    int burst_time[] = { 10, 5, 8 }; //Burst times for each PID
    int n = sizeof(processes) / sizeof(processes[0]); //num of processes. Also for countng contents of an array
    fifo(processes, n, burst_time); //call fifo function

    return 0;
}