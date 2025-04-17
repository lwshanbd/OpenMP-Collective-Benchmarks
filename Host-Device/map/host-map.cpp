#include <cstdio>
#include <omp.h>

#define MIN_SIZE 1024
#define MAX_SIZE 1024 * 1024 * 1024

int main(int argc, char *argv[]) {
    int nDevs = omp_get_num_devices();
    printf("Number of devices: %d\n", nDevs);

    for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2) {
        int *a = (int *)malloc(size * sizeof(int));

        auto start = omp_get_wtime();
        #pragma omp parallel for
        for (int i = 0; i < nDevs; i++) {
            #pragma omp target data map(to: a[0:size]) device(i)
        }
        auto end = omp_get_wtime();
        printf("Time taken: %fs for size %zu\n", end - start, size);
    }
}