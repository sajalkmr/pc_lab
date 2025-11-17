#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r) {
    int i=l, j=m+1, k=0;
    int *temp = (int*)malloc((r-l+1)*sizeof(int));

    while (i <= m && j <= r)
        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = temp[k];

    free(temp);
}

void mergeSortSeq(int a[], int l, int r) {
    if (l >= r) return;
    int m = (l+r)/2;
    mergeSortSeq(a, l, m);
    mergeSortSeq(a, m+1, r);
    merge(a, l, m, r);
}

void mergeSortPar(int a[], int l, int r, int depth) {
    if (l >= r) return;
    int m = (l+r)/2;

    if (depth < 4) {
        #pragma omp task
        mergeSortPar(a, l, m, depth+1);

        #pragma omp task
        mergeSortPar(a, m+1, r, depth+1);

        #pragma omp taskwait
    } else {
        mergeSortSeq(a, l, m);
        mergeSortSeq(a, m+1, r);
    }

    merge(a, l, m, r);
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int *arr = malloc(n*sizeof(int));
    int *seq = malloc(n*sizeof(int));
    int *par = malloc(n*sizeof(int));

    for (int i=0; i<n; i++)
        arr[i] = rand() % 100000;

    for (int i=0; i<n; i++) seq[i] = par[i] = arr[i];

    double t1 = omp_get_wtime();
    mergeSortSeq(seq, 0, n-1);
    double t2 = omp_get_wtime();

    printf("Sequential: %f sec\n", t2 - t1);

    double t3 = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortPar(par, 0, n-1, 0);
    }
    double t4 = omp_get_wtime();

    printf("Parallel:   %f sec\n", t4 - t3);

    free(arr); free(seq); free(par);
    return 0;
}
