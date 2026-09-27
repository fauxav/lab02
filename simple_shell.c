#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char command[100]; // input goes here
    pid_t pid; //pid holds value of fork()

    while (1) { //use while (1) because it's always true, so the loop never ends unless we use ctrl c
        printf("my-simple0-shell> "); // prints prompt
        fgets(command, sizeof(command), stdin);
         // the second line pauses program and waits for user input. Once user presses enter, the command 
         // EXAMPLE: if we type 1s, command holds '1', 's',  '\n', and '\0' (USED LATER)

        //remove newline character
        command[strcspn(command, "\n")] = '\0'; //strcspn(command, "\n") counts how many characters before \n
        //this overwrites \n so now command is jsut 1s 
        pid = fork(); //split into 2 processes. 
        if (pid == 0) {
            execlp(command, command, (char*) NULL); //execute command
            perror("execlp failed");
            exit(1);
        } else if (pid > 0) {
            waitpid(pid, NULL, 0); //wait for child process to terminate
        } else {
            perror("fork failed");
        }
    }
    return 0;
}
