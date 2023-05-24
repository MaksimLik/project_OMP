#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// gcc not_omp.c -o not_omp

int main(int argc, char* argv[]) {
 
    clock_t start, end;
    double diff;
 
    int range;  // inicjowanie zakresu
    if (argc > 1) range = atoi(argv[1]);
 
    int threads = 1;    // установка количества потоков в 1 для последовательного выполнения
    int* primes = (int*)malloc(range * sizeof(int));
    start = clock();
 
    // wypełnienie tablicy jedynkami
    for (int i = 3; i < range; i += 2)
        primes[i] = 1;
 
    // równoległe przeliczenie sita
    for (int i = 3; i <= range / 2; i += 2)
        if (primes[i] == 1)
            for (int j = i * 2; j < range; j += i)
                if (primes[j] == 1)
                    primes[j] = 0;
 
    // zliczenie pozostałych, które są liczbami pierwszymi
    int result = 1;
    for (int i = 3; i < range; i += 2) {
        result += primes[i];
    }
    free(primes);
    end = clock();
 
    diff = (double)(end - start) / CLOCKS_PER_SEC;
 
    printf("IIlość liczb pierwszych w zakresie %d bez OMP wynosi %d czas: %f\n", range, result, diff);
 
    return 0;
}
