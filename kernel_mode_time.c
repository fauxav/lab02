#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Using a system call to read from standard input...\n");

    char buffer[100]; // where input gets stored, OS allocates memory to use
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
    // read() is a system call or a request to the kernel. STDIN_FILENO is where to read from, buffer is what we inputted, or the program's memory, and sizeof(buffer) is how many bytes to read

    if (bytes_read > 0) {
        printf("Read %ld bytes: %s\n", bytes_read, buffer);
    } else {
        printf("Failed to read. \n");
    }
    // This code block checks if our read was successful.

    return 0;
}