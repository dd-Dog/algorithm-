# C/C++ 算法练习环境

这是一个用于练习算法题目的C/C++开发环境，包含完整的编译配置和目录结构。

## 📁 目录结构

```
algorithm/
├── problems/          # 算法题目解决方案
│   └── two_sum.cpp   # 示例题目：两数之和
├── templates/         # 代码模板
│   ├── template.cpp  # C++模板
│   └── template.c    # C模板
├── utils/            # 工具函数
│   ├── common.h      # 常用工具函数（C++）
│   ├── performance.h # 性能统计工具（C/C++）
│   └── README.md     # 工具库使用说明
├── build/            # 编译输出目录（自动生成）
│   └── bin/          # 可执行文件
├── tests/            # 测试用例（可选）
├── CMakeLists.txt    # CMake配置文件
├── Makefile          # Make编译文件
├── compile.bat       # Windows批处理编译脚本
├── run.bat           # 快速编译运行单个文件
├── run_debug.bat     # 快速编译运行（调试模式）
└── README.md         # 本文件
```

## 🚀 快速开始

### 方法一：使用CMake（推荐）

```bash
# 创建build目录
mkdir build
cd build

# 生成Makefile
cmake ..

# 编译
cmake --build .

# 运行示例
./bin/two_sum        # Linux/Mac
.\bin\two_sum.exe    # Windows
```

### 方法二：使用Makefile

```bash
# 编译所有文件
make

# 运行示例
make run-example

# 清理编译文件
make clean
```

### 方法三：使用批处理脚本（Windows）

```bash
# 直接运行编译脚本
compile.bat

# 运行编译后的程序
build\bin\two_sum.exe
```

### 方法四：快速编译运行（推荐用于调试）⭐

这是最快捷的方式，适合快速测试单个文件：

```bash
# 方式1: 使用 run.bat（最灵活）
run.bat problems\01_utra_quicksort.c          # 编译并运行
run.bat problems\01_utra_quicksort.c debug    # 调试模式（带-g选项）

# 方式3: 使用 run_debug.bat（调试模式）
run_debug.bat problems\01_utra_quicksort.c
```

**特点：**
- ✅ 自动检测C/C++文件类型
- ✅ 自动选择gcc或g++编译器
- ✅ 自动包含utils目录
- ✅ 编译后立即运行
- ✅ 支持调试模式（-g -O0）
- ✅ 显示编译状态和运行结果

### 方法五：手动编译

```bash
# 编译单个C++文件
g++ -std=c++17 -Wall -Wextra -O2 -I./utils -o build/bin/two_sum problems/two_sum.cpp

# 编译单个C文件
gcc -Wall -Wextra -O2 -I./utils -o build/bin/example problems/example.c
```

## ⚡ 快速调试技巧

### 在编辑器中快速运行

1. **使用快捷键**：在VS Code中，可以配置任务或使用终端快捷键
2. **右键运行**：在文件资源管理器中右键点击 `.bat` 文件选择"运行"
3. **命令行快速运行**：
   ```bash
   # 最快捷的方式
   quick_run.bat 01_utra_quicksort.c
   ```

### 调试模式

使用调试模式编译，可以：
- 使用GDB调试器进行断点调试
- 查看变量值
- 单步执行

```bash
# 编译为调试版本
run.bat problems\01_utra_quicksort.c debug

# 使用GDB调试
gdb build\bin\01_utra_quicksort_debug.exe
```

## 📝 使用模板

创建新题目时，可以复制模板文件：

```bash
# 复制C++模板
cp templates/template.cpp problems/your_problem.cpp

# 复制C模板
cp templates/template.c problems/your_problem.c
```

## 🛠️ 环境要求

- **编译器**: GCC (g++) 或 Clang
  - Windows: 安装 [MinGW-w64](https://www.mingw-w64.org/) 或使用 [MSYS2](https://www.msys2.org/)
  - Linux: `sudo apt-get install build-essential` (Ubuntu/Debian)
  - Mac: `xcode-select --install`
  
- **CMake** (可选，用于方法一)
  - Windows: 从 [CMake官网](https://cmake.org/download/) 下载
  - Linux: `sudo apt-get install cmake`
  - Mac: `brew install cmake`

## 📚 添加新题目

1. 在 `problems/` 目录下创建新的 `.cpp` 或 `.c` 文件
2. 使用模板文件作为起点
3. 编写解决方案
4. 使用上述任一方法编译运行

## 🧪 测试

可以在代码中添加测试用例，或者使用 `tests/` 目录存放测试数据文件。

## 💡 提示

### 使用工具函数

- **性能统计**: 使用 `#include "performance.h"` 引入性能统计工具
  ```c
  #include "performance.h"
  
  // 方式1: 手动记录
  clock_t start = clock();
  long long start_mem = get_memory_usage();
  // ... 你的算法 ...
  clock_t end = clock();
  long long end_mem = get_memory_usage();
  print_performance_stats(start, end, start_mem, end_mem);
  
  // 方式2: 使用PerformanceTimer（更简洁）
  PerformanceTimer timer;
  performance_start(&timer);
  // ... 你的算法 ...
  performance_end(&timer);
  performance_print(&timer);
  ```

- **C++工具**: 使用 `#include "common.h"` 引入常用工具函数（C++）

### 其他提示

- 模板中已包含常用的头文件和优化设置
- 编译选项已包含 `-Wall -Wextra` 用于警告检查
- 使用 `-O2` 优化级别以获得更好的性能
- 所有工具函数都在 `utils/` 目录下，详见 `utils/README.md`

## 📖 学习资源

- [LeetCode](https://leetcode.cn/) - 算法练习平台
- [C++ Reference](https://en.cppreference.com/) - C++标准库参考
- [算法导论](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/) - 经典算法教材

## 🔧 故障排除

### 找不到编译器
- 确保编译器已安装并添加到系统PATH
- Windows用户可以使用 `where g++` 检查

### CMake找不到
- 确保CMake已安装
- 检查版本：`cmake --version`

### 编译错误
- 检查代码语法
- 确保所有必要的头文件都已包含
- 查看编译器的错误信息

## 📄 许可证

本项目仅供学习使用。
