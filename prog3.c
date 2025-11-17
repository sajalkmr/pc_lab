#include <stdio.h>
#include <omp.h>
#include <time.h>

int ser_fib(int n) {
    if (n < 2) return n;
    return ser_fib(n - 1) + ser_fib(n - 2);
}

int par_fib(int n) {
    if (n < 2) return n;
    int x, y;

    #pragma omp task shared(x)
    x = par_fib(n - 1);

    #pragma omp task shared(y)
    y = par_fib(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n, result;
    clock_t start, end;
    double cpu_time;

    printf("Enter n: ");
    scanf("%d", &n);

    start = clock();
    #pragma omp parallel
    {
        #pragma omp single
        result = par_fib(n);
    }
    end = clock();
    cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nParallel Fibonacci(%d) = %d", n, result);
    printf("\nTime taken (parallel): %f sec", cpu_time);

    start = clock();
    result = ser_fib(n);
    end = clock();
    cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n\nSerial Fibonacci(%d) = %d", n, result);
    printf("\nTime taken (serial): %f sec\n", cpu_time);

    return 0;
}
