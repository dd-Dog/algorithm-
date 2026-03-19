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


#define MAXN 1000005
int pi[MAXN];
char s[MAXN];
int occ[MAXN];
// ============================================
// 算法实现区域
// ============================================

// 在这里实现你的算法函数
int solve() {
    scanf("%s", s);

    printf("%s\n", s);
    int n = strlen(s);
    //找最大相同的前缀和后缀p，且该子串至少在中间出现过一次
    //思路：一次遍历txt，确定[0,i]的子串的最大相同前后缀长度，保存到pi[i]中
    //令L[pi[i]]=1（pi[i]>0），即L[s]表示[0,s]的前缀在txt本身或者其子串中也是后缀
    //遍历L[s]，从最大的s开始
    for(int i=1; i<n; i++){
        int j = pi[i-1];
        while(j>0 && s[i]!=s[j])
            j = pi[j-1];
        if(s[i]==s[j]) j++;
        pi[i] = j;
    }
    for(int i=0; i<n-1; i++){
        occ[pi[i]] = 1;
    }
    
    int L = pi[n-1];
    printf("=======\n");
    while(L>0){
        printf("%d\n", L);
        if(occ[L] > 0){
            s[L] = '\0';
            printf("%s\n", s);
            return 0;
        }
        L = pi[L-1];
    }
    return 1;
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
