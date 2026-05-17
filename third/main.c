#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000000
#define THREADS 4

long long array[SIZE];
long long partial_sum[THREADS];

typedef struct {
    int start;
    int end;
    int index;
} ThreadData;

void* sum_part(void* arg) {

    ThreadData* data = (ThreadData*)arg;

    long long sum = 0;

    for (int i = data->start; i < data->end; i++) {
        sum += array[i];
    }

    partial_sum[data->index] = sum;

    return NULL;
}

int main() {

    pthread_t threads[THREADS];
    ThreadData tdata[THREADS];

    // Инициализация массива
    for (int i = 0; i < SIZE; i++) {
        array[i] = 1;
    }

    int chunk = SIZE / THREADS;

    // Создание потоков
    for (int i = 0; i < THREADS; i++) {

        tdata[i].start = i * chunk;
        tdata[i].end = (i == THREADS - 1) ? SIZE : (i + 1) * chunk;
        tdata[i].index = i;

        pthread_create(&threads[i], NULL, sum_part, &tdata[i]);
    }

    // Ожидание завершения потоков
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Суммирование результатов
    long long total = 0;

    for (int i = 0; i < THREADS; i++) {
        total += partial_sum[i];
    }

    printf("Total sum = %lld\n", total);

    return 0;
}