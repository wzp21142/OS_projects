#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct complex{
    double real;
    double imaginary;
}complex;
typedef struct calculator{
    complex a;
    complex b;
    char symbol;
}calculator;

void *Calc(void * calc) {
    complex *ans = (complex *)malloc(sizeof(complex));
    calculator* nums = (calculator *)calc;
    if(nums->symbol=='+'){
        printf("Thread is calculating (%.2f + %.2fi) + (%.2f +%.2fi)\n", nums->a.real, nums->a.imaginary, nums->b.real, nums->b.imaginary);
        ans->real = nums->a.real+ nums->b.real;
        ans->imaginary = nums->a.imaginary + nums->b.imaginary;
    }
    pthread_exit((void *)ans);
}

int main(int argc, char *argv[]) {
    pthread_t myThread;
    int rc;
    calculator nums;
    void *ans;
    nums.a.real = 5.0;
    nums.b.real = 5.0;
    nums.a.imaginary = 8.0;
    nums.b.imaginary = 10.0;
    nums.symbol = '+';
    rc = pthread_create(&myThread, NULL, Calc, &nums);
    if (rc) {
        perror("Failed in calling pthread_create\n");
        exit(-1);
    }
    pthread_join(myThread, &ans);
    complex* result = (complex *)ans;
    printf("Ans: %.2f + %.2fi\n", result->real, result->imaginary);
    return 0;
}