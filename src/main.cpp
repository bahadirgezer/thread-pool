#include <iostream>
#include <pthread.h>
#include <random>
#include <ctime>
#include "operations.h"

double (*functions[10])(const int *, int) =
        {min, max, range, mode, median,
         sum, arithmetic_mean, harmonic_mean,
         standart_deviation, interquartile_range};

double solutions[10];

bool taken[10];

void *distributer(void *array);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        // first program argument should be the length of the array
        // and the second should be the number of threads
        printf("Usage: ./program.out <array length> <number of threads>");
        return 1;
    }

    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    long array_length = strtol(argv[1], nullptr, 10);
    long num_threads = strtol(argv[2], nullptr, 10);
    num_threads = num_threads > 10 ? 10 : num_threads;

    // create an array of random numbers
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> randm(1000, 10000); // define the range

    int *array = new int[array_length];
    for (int i = 0; i < array_length; i++) {
        array[i] = (int) randm(gen);
    }

    // adds args with first arg being the array and the second arg being the number of threads
    void *args[3];
    args[0] = array;
    args[1] = reinterpret_cast<void *>(num_threads);
    args[2] = reinterpret_cast<void *>(array_length);

    // create an array of threads
    pthread_t *threads = new pthread_t[num_threads];
    for (int i = 0; i < num_threads; i++) {
        // pass the array and its length to the thread
        pthread_create(&threads[i], nullptr, distributer, args);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], nullptr);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    unsigned long toc = clock();

    for (int i = 0; i < 5; i++) {
        printf("%ld\n", (long) solutions[i]);
    }

    for (int i = 5; i < 10; i++) {
        // print the solutions with minimum 2 decimal places and maximum 5 decimal places
        // no scientific notation remove unnecessary zeros
        printf("%.5f\n", solutions[i]);
    }

    // print the time it took to calculate the solutions in seconds
    printf("%f\n", (double) (end.tv_sec - start.tv_sec) +
            (double) (end.tv_nsec - start.tv_nsec) / 1000000000.0);

    return 0;
}

void *distributer(void *args) {
    // get the array and its length from the args
    void **args_array = reinterpret_cast<void **>(args);
    int *array = reinterpret_cast<int *>(args_array[0]);
    int array_length = reinterpret_cast<long>(args_array[2]);

    for (int i = 0; i < 10; i++) {
        // divide the array into equal parts and pass them to the threads
        if (!taken[i]) {
            taken[i] = true;
            solutions[i] = functions[i](array, array_length);
        }
    }
    pthread_exit(nullptr);
}
