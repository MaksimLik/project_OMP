#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//gcc -fopenmp omp.c -o omp
 
int main(int argc, char* argv[]) {
 
    clock_t start, end;
    double diff;
 
    int range;  // inicjowanie zakresu
    if (argc > 1) range = atoi(argv[1]);
 
    int threads;    // inicjowanie liczby wątków
    if (argc > 2) threads = atoi(argv[2]);
 
    omp_set_num_threads(threads);
    int* primes = (int*)malloc(range * sizeof(int));
    start = clock();
 
    // wypełnienie tablicy jedynkami
    #pragma omp parallel for
    for (int i = 3; i < range; i += 2)
        primes[i] = 1;
 
    // równoległe przeliczenie sita
    #pragma omp parallel for schedule(dynamic)
    for (int i = 3; i <= range / 2; i += 2)
        if (primes[i] == 1)
            for (int j = i * 2; j < range; j += i)
                if (primes[j] == 1)
                    primes[j] = 0;
 
    // zliczenie pozostałych, które są liczbami pierwszymi
    int result = 1;
    #pragma omp parallel for reduction(+:result)
    for (int i = 3; i < range; i += 2) {
        result += primes[i];
    }
    free(primes);
    end = clock();
 
    diff = (double)(end - start) / CLOCKS_PER_SEC;
 
    printf("Ilość liczb pierwszych w zakresie %d policzona %d wątkami wynosi %d w czasie %f\n", range, threads, result, diff);
 
    return 0;
}