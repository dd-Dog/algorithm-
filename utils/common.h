#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 数组打印工具函数
// ============================================

/**
 * 打印一维整数数组
 * @param arr 数组指针
 * @param n 数组长度
 * @param name 数组名称（可选，传入NULL则不显示）
 */
static inline void print_int_array(int arr[], int n, const char* name) {
    if (name != NULL) {
        printf("%s: ", name);
    }
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

/**
 * 打印一维长整型数组
 * @param arr 数组指针
 * @param n 数组长度
 * @param name 数组名称（可选，传入NULL则不显示）
 */
static inline void print_longlong_array(long long arr[], int n, const char* name) {
    if (name != NULL) {
        printf("%s: ", name);
    }
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%lld", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

/**
 * 打印一维浮点数组
 * @param arr 数组指针
 * @param n 数组长度
 * @param name 数组名称（可选，传入NULL则不显示）
 */
static inline void print_double_array(double arr[], int n, const char* name) {
    if (name != NULL) {
        printf("%s: ", name);
    }
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%.2f", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

static inline void print_int_2d_array_fixed_2(int arr[][2], int rows, int cols) {
    // 注意：cols 应该是 2，这里直接硬编码也行
    for (int i = 0; i < rows; i++) {
        printf("[%d, %d]\n", arr[i][0], arr[i][1]);
    }
}

/**
 * 打印二维整数数组
 * @param arr 二维数组指针（或数组的数组）
 * @param rows 行数
 * @param cols 列数
 * @param name 数组名称（可选，传入NULL则不显示）
 */
static inline void print_int_2d_array(int** arr, int rows, int cols, const char* name) {
    if (name != NULL) {
        printf("%s:\n", name);
    }
    printf("[\n");
    for (int i = 0; i < rows; i++) {
        printf("  [");
        for (int j = 0; j < cols; j++) {
            printf("%d", arr[i][j]);
            if (j < cols - 1) printf(", ");
        }
        printf("]");
        if (i < rows - 1) printf(",");
        printf("\n");
    }
    printf("]\n");
}

/**
 * 打印二维整数数组（使用一维数组模拟，按行优先存储）
 * @param arr 一维数组指针
 * @param rows 行数
 * @param cols 列数
 * @param name 数组名称（可选，传入NULL则不显示）
 */
static inline void print_int_2d_array_flat(int arr[], int rows, int cols, const char* name) {
    if (name != NULL) {
        printf("%s:\n", name);
    }
    printf("[\n");
    for (int i = 0; i < rows; i++) {
        printf("  [");
        for (int j = 0; j < cols; j++) {
            printf("%d", arr[i * cols + j]);
            if (j < cols - 1) printf(", ");
        }
        printf("]");
        if (i < rows - 1) printf(",");
        printf("\n");
    }
    printf("]\n");
}

/**
 * 打印二维长整型数组（使用一维数组模拟，按行优先存储）
 * @param arr 一维数组指针
 * @param rows 行数
 * @param cols 列数
 * @param name 数组名称（可选，传入NULL则不显示）
 */
static inline void print_longlong_2d_array_flat(long long arr[], int rows, int cols, const char* name) {
    if (name != NULL) {
        printf("%s:\n", name);
    }
    printf("[\n");
    for (int i = 0; i < rows; i++) {
        printf("  [");
        for (int j = 0; j < cols; j++) {
            printf("%lld", arr[i * cols + j]);
            if (j < cols - 1) printf(", ");
        }
        printf("]");
        if (i < rows - 1) printf(",");
        printf("\n");
    }
    printf("]\n");
}

// ============================================
// 便捷宏定义
// ============================================

// 简化调用，不显示数组名称
#define PRINT_INT_ARR(arr, n) print_int_array(arr, n, NULL)
#define PRINT_LONGLONG_ARR(arr, n) print_longlong_array(arr, n, NULL)
#define PRINT_DOUBLE_ARR(arr, n) print_double_array(arr, n, NULL)
#define PRINT_INT_2D_ARR_FLAT(arr, rows, cols) print_int_2d_array_flat(arr, rows, cols, NULL)
#define PRINT_LONGLONG_2D_ARR_FLAT(arr, rows, cols) print_longlong_2d_array_flat(arr, rows, cols, NULL)

// 带名称的打印
#define PRINT_INT_ARR_NAMED(arr, n, name) print_int_array(arr, n, name)
#define PRINT_LONGLONG_ARR_NAMED(arr, n, name) print_longlong_array(arr, n, name)
#define PRINT_INT_2D_ARR_FLAT_NAMED(arr, rows, cols, name) print_int_2d_array_flat(arr, rows, cols, name)

#endif // COMMON_H
