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

void printArr(int arr[], int start, int end){
    for(int i=start; i<end; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int partition(int arr[], int left, int right){
    printf("partition left=%d, right=%d\n", left,right);
    printArr(arr, 0, 8);
    int pivot,i,j;
    pivot  = arr[left];
    i = left;
    j = right;
    while(i < j){
        printf("partition step1 i=%d j=%d---", i, j);
        while(arr[j] >= pivot && i<j) j--;
        printf("partition step2 i=%d j=%d---", i, j);
        arr[i] = arr[j];
        while(arr[i]<=pivot && i<j) i++;
        printf("partition step4 i=%d j=%d---", i, j);
        arr[j] = arr[i];            
    }
    arr[i] = pivot; 
    printArr(arr, 0, 8);
    return i;

}

void quicksort(int arr[], int left, int right) {
    printf("quicksort, left=%d, right=%d\n", left, right);
    if(left >= right) return;
    int mid = partition(arr, left, right);
    printf("mid=%d\n", mid);
    if(mid > left)
        quicksort(arr, left, mid-1);
    if(mid < right)
        quicksort(arr, mid+1, right);
}

void solve() {
    // TODO: 在这里填充你的算法代码
    int n;
    while (scanf("%d", &n)==1 && n != 0) {
        int arr[500000];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        //quicksort
        quicksort(arr, 0, n - 1);
        printArr(arr, 0, n);
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