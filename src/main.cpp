#include <iostream>
#include <pthread.h>

void *distributer(void *array);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // first program argument should be the length of the array
        // and the second should be the number of threads
        printf("Usage: ./program.out <array length> <number of threads>");
        return 1;
    }

    long array_length = strtol(argv[1], nullptr, 10);
    long num_threads = strtol(argv[1], nullptr, 10);

    // create an array of random numbers
    int *array = new int[array_length];
    for (int i = 0; i < array_length; i++) {
        array[i] = rand();
    }

    // create an array of threads
    auto *threads = new pthread_t[num_threads];

    bool operation_status[10] = {false};
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], nullptr, distributer, (void *) array);
    }

    return 0;
}

void *distributer(void *array) {

    pthread_exit(nullptr);
}
