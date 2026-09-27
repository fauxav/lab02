#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Attempting privileged operation...\n"); // just announces whats gonna happen
    //Directly accessing hardware (causes segmentation fault in user mode)
    int *ptr = (int*) 0xFFFF0000; //High address. Also creates a pointer, and 0xFFFF0000 jsut means that the program can jsut pick an addy from thin air
    // (int*) treat 0xFFFF0000 as a address
    *ptr = 0; //attempt to write to protected memory. Fails

    printf("Privileged operation successful!\n");
    // this never happens. process got killed in prev line
    return 0;
}