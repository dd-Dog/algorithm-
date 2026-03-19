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

/**
BM算法：根据坏前缀和好后缀原则，进行跳跃，减少匹配次数
1. 找出模式串中每个字符出现的最后位置，即最右位置，因为我们是从左往右比较，保证坏前缀时右边先匹配到
2. 每次比较时对齐，初始化对齐，以及跳跃后对齐
3. 从模式串的右向左依次比较
4. 坏字符：模式串中不匹配位置L-文本串中不匹配的字符在模式串中出现的最右位置
    如果比较到某个字符不匹配，记下文本串中不匹配字符如'E',在模式串中最右的位置如2，模式串中是啥不重要，如果模式串
   中没有这个字符，就为-1
5. 好前缀：如果模式串右侧已匹配部分字符，则看这些字符是否在模式串中还出现过，肯定在已匹配的前面（因为是从后面开始比较的）
    比如已匹配MPLE，则看MPLE, PLE, LE ,E是否在前面出现过，找到最后一次出现的位置，两个位置相减，找出最大值
6. 4和5的结果比较，跳跃移动最大值
*/
void bm_search(const char s[], int s_len, const char p[],const int p_len){
    // printf("s_len=%d,p_len=%d\n", s_len, p_len);
    if(s_len < p_len) {
        printf("-1\n");
        return;
    }
    int p_c_index[256];
    int index = p_len-1;

    
    for(int i=0; i<256; i++) p_c_index[i] = -1; //初始化
    
    for(int i=0; i<p_len; i++){
        p_c_index[(unsigned char)p[i]] = i;
    }
    // for(int i=0; i<256; i++){
    //     printf("%d ", p_c_index[i][0]);
    // }
    
    int found = 0;
    while(index < s_len){
        
        int bad_character = 0;

        //一轮比较

        int j = p_len-1;
        // printf("index=%d\n", index);
        for(int i=index;j>=0; i--,j--){
        //    printf("j=%d\n", j);
            if(s[i] != p[j]){
                //遇到坏字符，计算要跳跃的位置
                bad_character = j - p_c_index[(unsigned char)s[i]];
                if(bad_character<1) bad_character = 1;
                break;
            }
            //判断好后缀  实际应用中不实现也基本满足要求
          
        }
        // printf("2222 j=%d\n", j);
        // if(index == 19) break;

        if(j<0){
            if(found) printf(" ");
            printf("%d ",index - p_len + 1);
            found = 1;
            index += 1;
        }else {
            index += bad_character;
        }

        
    }
    if(!found) printf("-1\n");


}

//HEREISASIMPLEEXAMPLE
//EXAMPLE
//ababababa
//ababa

// 在这里实现你的算法函数
void solve() {
    // TODO: 在这里填充你的算法代码
    // 示例：读取输入

    char T[100005];
    char P[100005];
    scanf("%s", T);
    scanf("%s", P);

        // 记录开始时间和内存
    clock_t start_time = clock();
    long long start_memory = get_memory_usage();

    bm_search(T, strlen(T), P, strlen(P));

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
