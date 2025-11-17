#include <stdio.h>
#include <omp.h>
#include <math.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0) return 0;
    return 1;
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    double start_serial = omp_get_wtime();
    for (int i = 1; i <= n; i++)
        is_prime(i);
    double end_serial = omp_get_wtime();
    printf("\nSerial time:   %f sec\n", end_serial - start_serial);

    double start_parallel = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 1; i <= n; i++)
        is_prime(i);
    double end_parallel = omp_get_wtime();

    printf("Parallel time: %f sec\n", end_parallel - start_parallel);

    return 0;
}
