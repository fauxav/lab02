#include <stdio.h>
#include <setjmp.h>

jmp_buf buf; //define global var (var outside of any func or block, allowng for access across any part of the program)
//holds jump buffer as well.
//buf is where prog current execution context is saved

void func1() {
    printf("In func1\n");
    longjmp(buf, 1); //jump to loc saved by setjmp with val 1

}

void func2() {
    printf("In func2\n");
    longjmp(buf, 2); //jump to loc saved by setjmp with val 2
}

void func3() {
    printf("In func3\n");
}

int main() {
    int val = setjmp(buf); //save current execution context in buf
    if (val == 0) {
        func1(); //initial jump to func1
    } else if (val == 1) {
        func2(); //return after jumping from func1
    } else if (val == 2) {
        func3(); //return after jumping from func2
    }
    return 0;
}