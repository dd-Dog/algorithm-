cmake_minimum_required(VERSION 3.10)
project(AlgorithmPractice C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/utils)

# 添加所有problems目录下的源文件
file(GLOB_RECURSE PROBLEM_SOURCES "problems/*.cpp" "problems/*.c")
foreach(SOURCE ${PROBLEM_SOURCES})
    get_filename_component(NAME ${SOURCE} NAME_WE)
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/utils)
endforeach()

# 添加模板示例
add_executable(template_cpp templates/template.cpp)
target_include_directories(template_cpp PRIVATE ${CMAKE_SOURCE_DIR}/utils)

add_executable(template_c templates/template.c)
target_include_directories(template_c PRIVATE ${CMAKE_SOURCE_DIR}/utils)
