#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <time.h>

// 引入性能统计工具
#include "performance.h"
// 常用工具函数可以放在这里
// #include "common.h"

// ============================================
// 算法实现区域
// ============================================

// 在这里实现你的算法函数
void solve() {
    // TODO: 在这里填充你的算法代码
    // 示例：读取输入
    int T,m;
    int a[100000];
    scanf("%d", &T);
    for(int i=0; i<T; i++){
        scanf("%d", &m);
        for(int j=0; j<m;j++){
            
        }
         // 记录开始时间和内存
        clock_t start_time = clock();
        long long start_memory = get_memory_usage();


        // 记录结束时间和内存
        clock_t end_time = clock();
        long long end_memory = get_memory_usage();
        // 打印性能统计
        print_performance_stats(start_time, end_time, start_memory, end_memory);
    }
    
}

// ============================================
// 主函数
// ============================================

int main() {
    // ============================================
    // 执行算法
    // ============================================
    solve();
    
    return 0;
}
