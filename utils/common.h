#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

// 打印vector
template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// 打印二维vector
template<typename T>
void print2DVector(const std::vector<std::vector<T>>& vec) {
    std::cout << "[" << std::endl;
    for (const auto& row : vec) {
        std::cout << "  ";
        printVector(row);
    }
    std::cout << "]" << std::endl;
}

// 字符串分割
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 快速输入输出优化宏
#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

#endif // COMMON_H
