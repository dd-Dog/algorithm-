#include <stdio.h>
#include <string.h>

#define MAXN 1000005

char s[MAXN];
int pi[MAXN];
int occ[MAXN];

int main() {
    scanf("%s", s);
    int n = strlen(s);
    //找最大相同的前缀和后缀p，且该子串至少在中间出现过一次
    //思路：一次遍历txt，确定[0,i]的子串的最大相同前后缀长度，保存到pi[i]中
    //令L[pi[i]]=1（pi[i]>0），即L[s]表示[0,s]的前缀在txt本身或者其子串中也是后缀
    //遍历L[s]，从最大的s开始
    // ===== 1. 计算 π 数组  实际中j指针在低位，i指针在高位=====
    // 0    1    2   3   4    5   6
    // A    B    A   B   A    B   C    s[i]?=s[j]
    // j    i                          s[1]!=s[0],j=0, pi[1]=0
    // j -> j   i                      s[2]==s[0],j=1, pi[2]=1
    //      j-> j   i                  s[3]==s[1],j=2, pi[3]=2
    //          j-> j    i             s[4]==s[2],j=3, pi[4]=3
    //              j->  j    i        s[5]==s[3],j=4, pi[5]=4
    // j <---   j <---   j       i    s[6]!=s[4],j=pi[j-1]=2,s[6]!=s[2],j=pi[j-1]=0,s[6]!=s[0],pi[6]=0
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }

    // ===== 2. 统计中间出现情况 =====  某个长度 L 是否在字符串内部出现过
    for (int i = 0; i < n - 1; i++) //i [0,n-2]，防止后缀被当作在中间出现
        occ[pi[i]] = 1;

    // ===== 3. 从最长前后缀开始找 =====
    int L = pi[n - 1];

    while (L > 0) {
        if (occ[L]) {
            s[L] = '\0';
            printf("%s\n", s);
            return 0;
        }
        L = pi[L - 1];
    }

    printf("Just a legend\n");
    return 0;
}

/**
Description

有一个字符串,让你找到这个字符串 S 里面的子串T. 这个子串 T 必须满足既是这个串的前缀，也是这个串的后缀，并且在字符串中也出现过一次的(提示：要求满足前后缀的同时也要在字符串中出现一次，只是前后缀可不行。输出最长满足要求字符串)

Input
给出一个字符串 长度 1 到 1e6 全部是小写字母

Output
如果找的到就输出这个子串 T 如果不行就输出 Just a legend

Sample Input 1 
fixprefixsuffix

Sample Output 1 
fix

Hint
字符串长度不大于 100
*/