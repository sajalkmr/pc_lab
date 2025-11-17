#include <stdio.h>
#include <omp.h>

int main() {
    int n, threads;
    printf("Enter number of iterations: ");
    scanf("%d", &n);
    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    int owner[n];

    #pragma omp parallel for schedule(static,2)
    for (int i = 0; i < n; i++)
        owner[i] = omp_get_thread_num();

    for (int i = 0; i < n; i += 2) {
        int t = owner[i];
        if (i + 1 < n)
            printf("Thread %d : Iterations %d -- %d\n", t, i, i+1);
        else
            printf("Thread %d : Iteration %d\n", t, i);
    }

    return 0;
}
