#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#endif

/**
 * 获取当前进程的内存使用量（KB）
 * @return 内存使用量（KB），失败返回-1
 */
static inline long long get_memory_usage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024; // 转换为KB
    }
    return -1;
#else
    // Linux/Mac可以使用其他方法，这里返回-1表示不支持
    return -1;
#endif
}

/**
 * 打印性能统计信息
 * @param start_time 开始时间（clock_t）
 * @param end_time 结束时间（clock_t）
 * @param start_memory 开始内存（KB）
 * @param end_memory 结束内存（KB）
 */
static inline void print_performance_stats(clock_t start_time, clock_t end_time, 
                                           long long start_memory, long long end_memory) {
    double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    printf("\n");
    printf("========================================\n");
    printf("性能统计信息\n");
    printf("========================================\n");
    printf("CPU 时间: %.6f 秒 (%.3f 毫秒)\n", cpu_time_used, cpu_time_used * 1000);
    
#ifdef _WIN32
    if (start_memory >= 0 && end_memory >= 0) {
        long long memory_used = end_memory - start_memory;
        printf("内存使用: %lld KB (%.2f MB)\n", 
               end_memory, end_memory / 1024.0);
        if (memory_used > 0) {
            printf("内存增长: +%lld KB (%.2f MB)\n", 
                   memory_used, memory_used / 1024.0);
        } else if (memory_used < 0) {
            printf("内存减少: %lld KB (%.2f MB)\n", 
                   memory_used, memory_used / 1024.0);
        }
    }
#else
    printf("内存统计: 需要Windows系统支持\n");
#endif
    
    printf("========================================\n");
}

/**
 * 性能测量结构体（可选，用于更高级的用法）
 */
typedef struct {
    clock_t start_time;
    clock_t end_time;
    long long start_memory;
    long long end_memory;
} PerformanceTimer;

/**
 * 开始性能测量
 * @param timer 性能计时器指针
 */
static inline void performance_start(PerformanceTimer* timer) {
    timer->start_time = clock();
    timer->start_memory = get_memory_usage();
}

/**
 * 结束性能测量
 * @param timer 性能计时器指针
 */
static inline void performance_end(PerformanceTimer* timer) {
    timer->end_time = clock();
    timer->end_memory = get_memory_usage();
}

/**
 * 打印性能统计（使用PerformanceTimer）
 * @param timer 性能计时器指针
 */
static inline void performance_print(PerformanceTimer* timer) {
    print_performance_stats(timer->start_time, timer->end_time, 
                           timer->start_memory, timer->end_memory);
}

#endif // PERFORMANCE_H
