#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------
// 1. Работа с одиночным указателем
// --------------------------------------
void demoPointer() {
    printf("\n--- 1. Работа с указателем ---\n");

    int *ptr = NULL;

    if (ptr == NULL) {
        printf("[INFO] ptr == NULL, выделяем память...\n");
        ptr = (int *)malloc(sizeof(int));
    }

    if (ptr == NULL) {
        printf("[ERROR] Не удалось выделить память\n");
        return;
    }

    *ptr = 42;
    printf("[OK] Значение: %d\n", *ptr);

    free(ptr);
    ptr = NULL;

    if (ptr == NULL) {
        printf("[OK] Указатель обнулён\n");
    }
}

// --------------------------------------
// 2. Работа с массивом через указатель
// --------------------------------------
void demoArray() {
    printf("\n--- 2. Работа с массивом ---\n");

    int *arr = (int *)malloc(5 * sizeof(int));

    if (arr == NULL) {
        printf("[ERROR] malloc failed\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }

    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    arr = NULL;

    if (arr == NULL) {
        printf("[OK] Массив безопасно очищен\n");
    }
}

// --------------------------------------
// 3. Проверка границ (защита от ошибок)
// --------------------------------------
void safeAccess(int *arr, int size, int index) {

    if (arr == NULL) {
        printf("[ERROR] NULL pointer\n");
        return;
    }

    if (index < 0 || index >= size) {
        printf("[PROTECT] index %d out of bounds\n", index);
        return;
    }

    printf("[OK] arr[%d] = %d\n", index, arr[index]);
}

void demoBounds() {
    printf("\n--- 3. Проверка границ ---\n");

    int *arr = (int *)malloc(3 * sizeof(int));

    if (arr == NULL) {
        printf("[ERROR] malloc failed\n");
        return;
    }

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    safeAccess(arr, 3, 1);
    safeAccess(arr, 3, 10);

    free(arr);
    arr = NULL;
}

// --------------------------------------
// 4. Работа с строкой (память + копирование)
// --------------------------------------
void demoString() {
    printf("\n--- 4. Работа со строками ---\n");

    char *str = (char *)malloc(50 * sizeof(char));

    if (str == NULL) {
        printf("[ERROR] malloc failed\n");
        return;
    }

    strcpy(str, "Safe pointer demo in C");

    printf("[OK] String: %s\n", str);

    free(str);
    str = NULL;

    if (str == NULL) {
        printf("[OK] String memory cleared\n");
    }
}

// --------------------------------------
// 5. Симуляция "безопасного создания ресурса"
// --------------------------------------
void demoFile() {
    printf("\n--- 5. Работа с файлом ---\n");

    FILE *file = fopen("test.txt", "w");

    if (file == NULL) {
        printf("[ERROR] file open failed\n");
        return;
    }

    fprintf(file, "C safe pointer demo\n");

    fclose(file);
    file = NULL;

    if (file == NULL) {
        printf("[OK] file pointer cleared\n");
    }
}

// --------------------------------------
// MAIN
// --------------------------------------
int main() {

    printf("=== Задание 2: Безопасные указатели в C ===\n");

    demoPointer();
    demoArray();
    demoBounds();
    demoString();
    demoFile();

    printf("\n[OK] Задание выполнено успешно\n");

    return 0;
}