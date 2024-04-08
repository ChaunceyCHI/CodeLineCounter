#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// 统计单个文件的行数
int countLinesInFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "找不到文件：" << filename << std::endl;
        return 0;
    }

    int lines = 0;
    std::string line;
    while (std::getline(file, line)) {
        // 排除空行
        if (!line.empty()) { 
            lines++; }
    }

    file.close();
    return lines;
}

// 函数用于递归统计文件夹中所有代码文件的行数
int countLinesInFolder(const std::string& folderPath, const std::vector<std::string>& extensions) {
    int totalLines = 0;
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) { // entry表示每次迭代返回的结果，recursive_directory_iterator函数作用为遍历目录下的子文件夹和文件
        if (entry.is_regular_file()) { // 判断是否为常规文件 
            std::string extension = entry.path().extension().string(); // 获取此文件的拓展名，并转换为string
            if (std::find(extensions.begin(), extensions.end(), extension) != extensions.end()) { // 容器的末尾位置并不包含有效元素，它指向有效元素后一位，用于标志容器的结束位置
                totalLines += countLinesInFile(entry.path().string());
            }
        }
    }
    return totalLines;
}

int main() {
    std::string folderPath;
    std::cout << "请输入目录路径：";
    std::getline(std::cin, folderPath);

    std::vector<std::string> extensions = { ".cpp", ".h" }; // 默认统计 .cpp 和 .h 文件的行数
    std::cout << "添加额外的拓展名（用空格隔开），或按下回车直接进行统计（默认统计 .cpp 和 .h 文件）： ";
    std::string inputExtensions;
    std::getline(std::cin, inputExtensions);
    std::istringstream iss(inputExtensions);
    std::string extension;
    while (iss >> extension) {
        extensions.push_back(extension);
    }

    int totalLines = countLinesInFolder(folderPath, extensions);
    std::cout << "您的代码总行数为： " << totalLines << std::endl;

    return 0;
}
