//
// Created by Bahadır Gezer on 27.11.2022.
//
#include "operations.h"

double min(const int *array, int length) {
    double min = array[0];
    for (int i = 1; i < length; i++) {
        if (array[i] < min)
            min = array[i];
    }
    return min;
}

double max(const int *array, int length) {
    double max = array[0];
    for (int i = 1; i < length; i++) {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

double range(const int *array, int length) {
    double min = array[0];
    double max = array[0];
    for (int i = 1; i < length; i++) {
        if (array[i] < min)
            min = array[i];
        if (array[i] > max)
            max = array[i];
    }
    return max - min;
}

double mode(const int *array, int length) {
    int mode = array[0];
    int mode_count = 1;
    for (int i = 1; i < length; i++) {
        int count = 1;
        for (int j = i + 1; j < length; j++) {
            if (array[i] == array[j])
                count++;
        }
        if (count > mode_count) {
            mode = array[i];
            mode_count = count;
        }
    }
    return (double) mode;
}

double median(const int *array, int length) {
    int *sorted_array = new int[length];
    for (int i = 0; i < length; i++) {
        sorted_array[i] = array[i];
    }
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (sorted_array[i] > sorted_array[j]) {
                int temp = sorted_array[i];
                sorted_array[i] = sorted_array[j];
                sorted_array[j] = temp;
            }
        }
    }
    double median;
    if (length % 2 == 0)
        median = (sorted_array[length / 2] + sorted_array[length / 2 - 1]) / 2;
    else
        median = sorted_array[length / 2];
    delete[] sorted_array;
    return median;
}

double sum(const int *array, int length) {
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += array[i];
    }
    return sum;
}

double arithmetic_mean(const int *array, int length) {
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += array[i];
    }
    return sum / length;
}

double harmonic_mean(const int *array, int length) {
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += 1 / (double) array[i];
    }
    return length / sum;
}

double standart_deviation(const int *array, int length) {
    double mean = arithmetic_mean(array, length);
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += (array[i] - mean) * (array[i] - mean);
    }
    return sum / length;
}

double interquartile_range(const int *array, int length) {
    int *sorted_array = new int[length];
    for (int i = 0; i < length; i++) {
        sorted_array[i] = array[i];
    }
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (sorted_array[i] > sorted_array[j]) {
                int temp = sorted_array[i];
                sorted_array[i] = sorted_array[j];
                sorted_array[j] = temp;
            }
        }
    }
    double q1, q3;
    if (length % 2 == 0) {
        q1 = (sorted_array[length / 4] + sorted_array[length / 4 - 1]) / 2;
        q3 = (sorted_array[length * 3 / 4] + sorted_array[length * 3 / 4 - 1]) / 2;
    } else {
        q1 = sorted_array[length / 4];
        q3 = sorted_array[length * 3 / 4];
    }
    delete[] sorted_array;
    return q3 - q1;
}
