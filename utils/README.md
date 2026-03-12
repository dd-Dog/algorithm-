# Utils 工具库

这个目录包含算法练习中常用的工具函数。

## 可用工具

### performance.h - 性能统计工具

提供算法执行时间和内存使用统计功能。

#### 基本用法

```c
#include "performance.h"

int main() {
    // 方式1: 手动记录时间
    clock_t start_time = clock();
    long long start_memory = get_memory_usage();
    
    // 你的算法代码
    solve();
    
    clock_t end_time = clock();
    long long end_memory = get_memory_usage();
    
    // 打印统计信息
    print_performance_stats(start_time, end_time, start_memory, end_memory);
    
    return 0;
}
```

#### 高级用法（使用PerformanceTimer）

```c
#include "performance.h"

int main() {
    PerformanceTimer timer;
    
    // 开始计时
    performance_start(&timer);
    
    // 你的算法代码
    solve();
    
    // 结束计时并打印
    performance_end(&timer);
    performance_print(&timer);
    
    return 0;
}
```

#### 函数说明

- `get_memory_usage()` - 获取当前进程内存使用量（KB），失败返回-1
- `print_performance_stats()` - 打印性能统计信息
- `performance_start()` - 开始性能测量
- `performance_end()` - 结束性能测量
- `performance_print()` - 打印性能统计（使用PerformanceTimer）

#### 输出示例

```
========================================
性能统计信息
========================================
CPU 时间: 0.001234 秒 (1.234 毫秒)
内存使用: 2048 KB (2.00 MB)
内存增长: +512 KB (0.50 MB)
========================================
```

### common.h - 通用工具函数（C++）

包含C++常用的工具函数，如打印vector、字符串分割等。

## 使用注意事项

1. **包含路径**: 编译时需要添加 `-I./utils` 选项（已自动配置）
2. **Windows内存统计**: 需要链接 `psapi` 库（已自动配置）
3. **跨平台**: 内存统计功能目前仅支持Windows，Linux/Mac会显示"需要Windows系统支持"
