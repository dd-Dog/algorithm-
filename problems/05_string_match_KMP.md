这道题是字符串算法里的经典题（CF《Just a legend》同型）。
**标准做法：KMP 的前缀函数（prefix function / π数组）**，时间复杂度 **O(N)**，空间 O(N)。

> 对于 |S| ≤ 1e6，这是唯一现实可行的主流解法之一。🚀

---

# 🎯 一、问题本质（形式化）

给字符串 S，找最长字符串 T，使：

1. T 是 S 的前缀
2. T 是 S 的后缀
3. T 在中间还出现过一次（不能只在首尾）

---

# 🧠 二、核心思想（KMP π数组）

定义：

👉 π[i] = S[0..i] 的最长「真前缀 = 真后缀」长度

例如：

```
S = ababcabab
π = 0 0 1 2 0 1 2 3 4
```

---

# 🏆 三、关键观察（解题核心）

令：

```
L = π[n−1]
```

👉 L = 最长前后缀长度

但还需要：

> 这个长度 L 在中间也出现过

---

## 如何判断“中间出现过”？

如果存在某个 i < n−1：

```
π[i] == L
```

则说明：

👉 该前缀在中间出现过

---

## 如果没有怎么办？

KMP 的精髓来了：

👉 较短的前后缀仍可能满足

下一个候选长度：

```
L = π[L−1]
```

不断递归。

---

# 📌 四、算法流程（标准）

```
计算 π 数组
L = π[n−1]

while L > 0:
    if L 在 π[0..n−2] 中出现过:
        输出 S[0..L−1]
        结束
    else:
        L = π[L−1]

如果 L = 0:
    输出 "Just a legend"
```

---

# 🚀 五、为什么是 O(N)

* π数组计算 O(N)
* 每个 L 只回退一次
* 总复杂度线性

---

# ✅ 六、C 语言标准实现（可直接交）

```c
#include <stdio.h>
#include <string.h>

#define MAXN 1000005

char s[MAXN];
int pi[MAXN];
int occ[MAXN];

int main() {
    scanf("%s", s);
    int n = strlen(s);

    // ===== 1. 计算 π 数组 =====
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }

    // ===== 2. 统计中间出现情况 =====
    for (int i = 0; i < n - 1; i++)
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
```

---

# 🔍 七、用样例验证

## 输入

```
fixprefixsuffix
```

## 输出

```
fix
```

---

