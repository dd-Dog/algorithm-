
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
/**
把动态规划分组/枚举划分/贪心直接分组问题 转化为 判定问题
即判定在最大分组和不超过K的情况下，是否可以分成M组，我们遍历的是K，而不是数据集本身
*/

//判断在每组的最大值是否可以不超过k情况下，能否分成少于M组（即K还可以再减小）
int check(int a[], int size, long long k, int m){
    // printf("size=%d,k=%d,m=%d\n", size,k,m);
    long long sum_group = 0;
    int group_num = 1;
    for(int i=0; i<size; i++){
        if(sum_group + a[i] > k){
            group_num++;
            sum_group = a[i];
            // printf("group_num=%d\n", group_num);
        }else {
            sum_group += a[i];
        }
    }
    return group_num <= m ? 1:0;
}

void solve() {
    // TODO: 在这里填充你的算法代码
    // 示例：读取输入
    int N,M;
    int a[1000];
    long long R = 0;  //记录最大值，初始化为0,一定要注意范围，否则OJ可能失败
    int L = 0;  //记录最小值，初始化为0
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        scanf("%d", &a[i]);
        L = max(L, a[i]);
        R += a[i];
    }
    printf("L=%d, R=%lld\n",L,R);
    // 记录开始时间和内存
    clock_t start_time = clock();
    long long start_memory = get_memory_usage();

    //二分遍历，每组的最大消费值，本质是查找+判定
    while(L < R) {
        long long mid = (L+R)/2;
        int r = check(a, N, mid, M);
        printf("r=%d\n", r);
        if(r==1){ //检查如果能满足，继续缩小K
            R = mid;
        }else {
            L = mid + 1;
        }
    }

    printf("%d\n", L);
    // 记录结束时间和内存
    clock_t end_time = clock();
    long long end_memory = get_memory_usage();
    // 打印性能统计
    print_performance_stats(start_time, end_time, start_memory, end_memory);
    
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
 

/*
Description

给出n天中每天的花费，需要将这些天分成m组，每组包含连续的一或多天，若第i组的花费为K i
，求一种分组方法使得K=max{K i}最小。

Input
输入数据第一行为两个正整数N和M，之后输入N个正整数，分别表示第i天的费用。输出包含一行，表示上面描述的K。

Output
对于每组数据，输出一个数表示最小的花费。

Sample Input 1 
7 5
100
400
300
100
500
101
400
Sample Output 1 
500
Hint

n≤100
*/