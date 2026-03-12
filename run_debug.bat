@echo off
chcp 65001 >nul
REM 快速编译运行（调试模式）
REM 用法: run_debug.bat <文件名>
REM 示例: run_debug.bat problems\01_utra_quicksort.c

if "%~1"=="" (
    echo 用法: run_debug.bat ^<文件名^>
    echo 示例: run_debug.bat problems\01_utra_quicksort.c
    exit /b 1
)

call run.bat %1 debug
