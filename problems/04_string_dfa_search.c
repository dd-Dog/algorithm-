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
// 字符串匹配
// ============================================

// 测试数据：字符数组形式
// Case 1: Text "hello world", Pattern "world", Expect 6
char txt1[] = "hello world";
char pat1[] = "world";

// Case 2: Text "abcdefg", Pattern "abc", Expect 0
char txt2[] = "abcdefg";
char pat2[] = "abc";

// Case 3: Text "abcdefg", Pattern "fg", Expect 5
char txt3[] = "abcdefg";
char pat3[] = "fg";

// Case 4: Text "abcdefg", Pattern "xyz", Expect -1
char txt4[] = "abcdefg";
char pat4[] = "xyz";

char txt5[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
char pat5[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";

int op_count = 0;



// brute-force 暴力查找
/* brute-force version1
disadventage:Brute-force algorithm needs backup for every mismatch
*/
int brute_force_v1(const char txt[], int txt_size, const char pat[], int pat_size) {
    if (pat_size <= 0 || txt_size < pat_size) return -1;
    for (int i = 0; i <= txt_size - pat_size; i++) {
        int j = 0;
        for (j = 0; j < pat_size; j++) {
            op_count++;
            if (txt[i + j] != pat[j]) break;          
        }
        if (j == pat_size) return i;
    }
    return -1;
}
/**
brute-force version2
i point to end of the sequence of already matched chars in text
j sotres # of the already matched chars(end of seqeunce in pattern)
*/
int brute_force_v2(const char txt[], int txt_size, const char pat[], int pat_size){
    if(pat_size <= 0 || txt_size < pat_size) return -1;
    int i,j;
    op_count = 0;
    for(i=0,j=0; i<txt_size && j<pat_size; i++){
        
        if(txt[i] == pat[j]){
            op_count ++;
            j++;
        }else {
            i -= j; //i回退更少
            j = 0;
        }
    }
    if(j==pat_size) return i-pat_size;
    else return -1;

}


/**
DFA 确定有限状态自动机
思想：对固定的pattern预告构造状态机，即对每个匹配的字符添加状态，每个状态下输入一人字符后是什么状态
*/
#define R 256
int dfa_search(const char txt[], const int txt_size,  const char pat[], const int pat_size){
    //先构建DFA数组 [输入字符][状态]
    int dfa[R][pat_size];
    int x = 0;

    // 初始化状态 0
    for (int c = 0; c < R; c++) {
        dfa[c][0] = 0;
    }
    dfa[(unsigned char)pat[0]][0] = 1;
    for(int j=1; j<pat_size; j++){

        for(int c=0; c<R; c++){
            dfa[c][j] = dfa[c][x];  //拷贝失败匹配
        }
        dfa[(unsigned char)pat[j]][j] = j+1;     //设置匹配
        x = dfa[(unsigned char)pat[j]][x];
    }

    int i=0,j=0;
    for(i=0; i<txt_size && j<pat_size; i++){
        j = dfa[(unsigned char)txt[i]][j];
        op_count ++;
    }
    if(j == pat_size) return i-pat_size;
    else return -1;
}


// 在这里实现你的算法函数
void solve(void) {
    struct { char *txt, *pat; int txt_len, pat_len; int expect; } tests[] = {
        { txt1, pat1, (int)strlen(txt1), (int)strlen(pat1), 6 },
        { txt2, pat2, (int)strlen(txt2), (int)strlen(pat2), 0 },
        { txt3, pat3, (int)strlen(txt3), (int)strlen(pat3), 5 },
        { txt4, pat4, (int)strlen(txt4), (int)strlen(pat4), -1 },
        { txt5, pat5, (int)strlen(txt5), (int)strlen(pat5), -1 },
    };
    // 记录开始时间和内存
    clock_t start_time = clock();
    long long start_memory = get_memory_usage();

    for (int i = 0; i < 5; i++) {
        op_count = 0;
        int pos = dfa_search(tests[i].txt, tests[i].txt_len, tests[i].pat, tests[i].pat_len);
        printf("Text: \"%s\", Pattern: \"%s\" => pos=%d,op_count=%d, expect=%d %s\n",
               tests[i].txt, tests[i].pat, pos,op_count, tests[i].expect, pos == tests[i].expect ? "OK" : "FAIL");
    }
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
