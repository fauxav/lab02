#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;
    int status;

    //create first child process
    pid1 = fork();
    if (pid1 == 0) {
        //child 1 process
        printf("Child 1 with PID %d\n", getpid());
        //exit child process
    }

    //create second child process
    pid2 = fork();
    if (pid2 == 0) {
        //child 2 process
        printf("Child 2 with PID %d\n", getpid());
        _exit(0); //exit child process
    }

    //parent process
    waitpid(pid1, &status, 0);
    printf("Child 1 exited with status %d\n", WEXITSTATUS(status));
    waitpid(pid2, &status, 0);
    printf("Child 2 exited with status %d\n", WEXITSTATUS(status));
    return 0;
    
}
