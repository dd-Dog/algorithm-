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
#include "common.h"

// ============================================
// 算法实现区域
// ============================================

//快速排序
int partition(int arr[], int left ,int right){
    int pivot = arr[left];
    int i = left;
    int j = right;
    while(i<j){
        while(arr[j] >= pivot && i<j){
            j--;
        }
        arr[i] = arr[j];
        while(arr[i] <= pivot && i<j){
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    return i;
}


void quicksort(int arr[], int left, int right){
    if (left >= right) return;
    int mid = partition(arr,left ,right);
    if(left < mid)
        quicksort(arr, left, mid-1);
    if(mid < right)
        quicksort(arr, mid+1, right);
}


// 在这里实现你的算法函数
void solve() {
    // TODO: 在这里填充你的算法代码
    // 示例：读取输入
    int T,m,max=0;
    int si[100000];
    int ti[100000];
    scanf("%d", &T);
    // printf("样例个数：%d\n", T);
    for(int i=0; i<T; i++){
        max=0;
        scanf("%d", &m);
        // printf("任务个数：%d\n", m);
        for(int j=0; j<m;j++){
            scanf("%d %d", &si[j], &ti[j]);
        }
         // 记录开始时间和内存
        clock_t start_time = clock();
        long long start_memory = get_memory_usage();

        //算法逻辑
        //先进行排序，再计算最大并发量
        //快速排序

        print_int_array(si,m,"si");
        print_int_array(ti,m,"ti");
        quicksort(si,0, m-1);
        quicksort(ti,0, m-1);
        print_int_array(si,m,"si");
        print_int_array(ti,m,"ti");

        
        int l=0,k=0,tmp=0;
        while(l<m && k<m){
            if(si[l]<=ti[k]){
                tmp++;
                l++;
            }else {
                tmp--;
                k++;
            }
            if(max<tmp) max = tmp;
        }
        printf("%d\n", max);
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

/*
Description

实验室需要购置一些计算资源。由于实验室管理员小K不知道要具体购买多少计算资源，所以小K会对大家的实验资源需求做统计。
假设此时一共有n条实验请求。每一个请求都包含两个数字 si, ti表示该条请求的实验开始时间和结束时间。
每个实验在进行时都需要耗费一个计算资源（包括开始和结束时间）。请问最少需要购置多少计算资源。

Input
第一行包含一个整数T，表示样例个数。
对于每个样例，第一行输入一个数字m表示请求数。
接下来m行包含两个数字 si, ti表示当前实验需求的开始时间和结束时间。

Output
对于每个样例，输出一个数字表示最少的计算资源需求。

Sample Input 1 
2
2
1 2
2 3
3
1 2
3 4
2 3
Sample Output 1 

2
2

Hint
1 <= T <= 100
1 <= m <= 100000
1 ≤ si, ti ≤ 1e9
*/