@echo off
chcp 65001 >nul
REM Windows批处理编译脚本

setlocal enabledelayedexpansion

REM 检查编译器
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ not found. Please install MinGW or add it to PATH.
    exit /b 1
)

REM 创建输出目录
if not exist "build\bin" mkdir build\bin

REM 编译选项
set CXXFLAGS=-std=c++17 -Wall -Wextra -O2
set CFLAGS=-Wall -Wextra -O2 -lpsapi
set INCLUDES=-I./utils

REM 编译problems目录下的所有C++文件
for %%f in (problems\*.cpp) do (
    if exist "%%f" (
        echo Compiling %%f...
        for %%n in ("%%f") do (
            set "name=%%~nf"
            g++ !CXXFLAGS! !INCLUDES! -o "build\bin\!name!.exe" "%%f"
        )
    )
)

REM 编译problems目录下的所有C文件
for %%f in (problems\*.c) do (
    if exist "%%f" (
        echo Compiling %%f...
        for %%n in ("%%f") do (
            set "name=%%~nf"
            gcc !CFLAGS! !INCLUDES! -o "build\bin\!name!.exe" "%%f"
        )
    )
)

REM 编译模板
if exist "templates\template.cpp" (
    echo Compiling template.cpp...
    g++ %CXXFLAGS% %INCLUDES% -o "build\bin\template_cpp.exe" "templates\template.cpp"
)

if exist "templates\template.c" (
    echo Compiling template.c...
    gcc %CFLAGS% %INCLUDES% -lpsapi -o "build\bin\template_c.exe" "templates\template.c"
)

echo.
echo Compilation complete! Executables are in build\bin\
pause
