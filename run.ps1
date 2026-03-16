# PowerShell版本的快速编译运行脚本
# 用法: .\run.ps1 <文件名> [debug]
# 示例: .\run.ps1 problems\02_最少计算资源.c

param(
    [Parameter(Mandatory=$true)]
    [string]$SourceFile,
    [string]$Mode = "release"
)

# 设置编码
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# 检查文件是否存在
if (-not (Test-Path $SourceFile)) {
    Write-Host "错误: 文件不存在: $SourceFile" -ForegroundColor Red
    exit 1
}

# 检查编译器
$compiler = $null
if (Get-Command gcc -ErrorAction SilentlyContinue) {
    if ($SourceFile -match '\.c$') {
        $compiler = "gcc"
    } else {
        $compiler = "g++"
    }
} elseif (Get-Command g++ -ErrorAction SilentlyContinue) {
    $compiler = "g++"
} else {
    Write-Host "错误: 未找到 gcc 或 g++ 编译器" -ForegroundColor Red
    Write-Host "请安装 MinGW 或将其添加到 PATH" -ForegroundColor Red
    exit 1
}

# 获取文件名（不含扩展名）
try {
    $fileInfo = Get-Item -LiteralPath $SourceFile
    $fileName = $fileInfo.BaseName
    Write-Host "文件名: $fileName" -ForegroundColor Gray
} catch {
    # 如果Get-Item失败，使用Path方法
    $fileName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)
    Write-Host "使用Path方法获取文件名: $fileName" -ForegroundColor Gray
}

# 创建输出目录
$outputDir = "build\bin"
if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
}

# 设置编译选项
if ($Mode -eq "debug") {
    Write-Host "[调试模式] 编译 $SourceFile..." -ForegroundColor Yellow
    $flags = "-Wall -Wextra -g -O0 -I./utils"
    $outputName = "${fileName}_debug.exe"
} else {
    Write-Host "[发布模式] 编译 $SourceFile..." -ForegroundColor Green
    $flags = "-Wall -Wextra -O2 -I./utils"
    $outputName = "${fileName}.exe"
}
$output = "$outputDir\$outputName"
Write-Host "输出文件: $output" -ForegroundColor Gray

# 如果是C++文件，添加C++标准
if ($SourceFile -notmatch '\.c$') {
    $flags = "-std=c++17 $flags"
} else {
    # C文件在Windows上需要链接psapi库用于内存统计
    $flags = "$flags -lpsapi"
}

# 编译
$compileCmd = "$compiler $flags -o `"$output`" `"$SourceFile`""
Write-Host "执行: $compileCmd" -ForegroundColor Gray
Invoke-Expression $compileCmd

if ($LASTEXITCODE -ne 0) {
    Write-Host "编译失败！" -ForegroundColor Red
    exit 1
}

Write-Host "编译成功: $output" -ForegroundColor Green
Write-Host ""
Write-Host "========== 运行程序 ==========" -ForegroundColor Cyan
Write-Host ""

# 运行程序 - 直接查找匹配的exe文件
$allExes = Get-ChildItem $outputDir -Filter "*.exe" -ErrorAction SilentlyContinue | Where-Object { $_.BaseName -like "*$fileName*" -or $_.BaseName -eq $fileName }
if ($allExes) {
    $exeToRun = $allExes[0].FullName
    Write-Host "运行: $exeToRun" -ForegroundColor Gray
    & $exeToRun
    $exitCode = $LASTEXITCODE
} else {
    Write-Host "错误: 找不到可执行文件" -ForegroundColor Red
    Write-Host "在目录 $outputDir 中查找包含 '$fileName' 的exe文件" -ForegroundColor Yellow
    exit 1
}

Write-Host ""
Write-Host "========== 程序结束 ==========" -ForegroundColor Cyan
Write-Host "退出代码: $exitCode" -ForegroundColor $(if ($exitCode -eq 0) { "Green" } else { "Red" })

exit $exitCode
