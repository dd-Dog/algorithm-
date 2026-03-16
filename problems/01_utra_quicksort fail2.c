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
统计逆序对的数量，即冒泡排序的交换次数（只能交换相邻元素）

复杂度仍然是N^2 没有复用归并排序统计逆序对
*/
long long merge(int a[], int left, int r, int mid){
    printf("merge l=%d,r=%d,mid=%d\n",left,r,mid);
    if(r<=left) return 0;
    if(left+1==r) if(a[left]>a[r]) return 1; else return 0;
    int i=left,j=mid,tmp=0,leftsum=0,rightsum=0;
    for(j=mid;j<=r;j++){
        while(i<mid){
            if(a[i]>a[j]) {
                tmp++; 
            }
            i++;
        }   
        i=left;
    }
    printf("tmp=%d\n", tmp);
    if(r-left>1){
        leftsum = merge(a,left,mid-1,(left+mid-1)/2);
        rightsum = merge(a,mid, r,(mid+r)/2);
        printf("leftsum=%d,rightsum=%d\n",leftsum, rightsum);
    }

    return leftsum+rightsum+tmp;
}

void solve(){
    int n;
    long long count;
    while (scanf("%d", &n)==1 && n != 0) {
        int arr[500000];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        count = merge(arr, 0, n - 1, n/2);
        printf("%lld\n", count);

    }
}
// ============================================
// 主函数
// ============================================

int main() {
    // 记录开始时间和内存
    clock_t start_time = clock();
    long long start_memory = get_memory_usage();
    
    // ============================================
    // 执行算法
    // ============================================
    solve();
    
    // 记录结束时间和内存
    clock_t end_time = clock();
    long long end_memory = get_memory_usage();
    
    // 打印性能统计
    print_performance_stats(start_time, end_time, start_memory, end_memory);
    
    return 0;
}

/*
Ultra-QuickSort

Contest Problem
Time Limit：C/C++ 1000MS，Other 2000MS
Memory Limit：C/C++ 128MB，Other 256MB
Description

In this problem, you have to analyze a particular sorting algorithm.
 The algorithm processes a sequence of n distinct integers by swapping two adjacent sequence 
 elements until the sequence is sorted in ascending order. For the input sequence 

9 1 0 5 4 , 

Ultra-QuickSort produces the output 

0 1 4 5 9 . 

Your task is to determine how many swap operations Ultra-QuickSort needs to perform 
in order to sort a given input sequence.

Input

The input contains several test cases. Every test case begins with a line that contains a single 
integer n < 500,000 – the length of the input sequence. Each of the the following n lines contains a single integer 0 ≤ a[i] ≤ 999,999,999, the i-th input sequence element. Input is terminated by a sequence of length n = 0. This sequence must not be processed.

Output

For every input sequence, your program prints a single line containing an integer number op, the minimum number of swap operations necessary to sort the given input sequence.

Sample Input 1 

5
9
1
0
5
4
3
1
2
3
0
Sample Output 1 

6
0
*/