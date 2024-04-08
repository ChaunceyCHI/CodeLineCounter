#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// ͳ�Ƶ����ļ�������
int countLinesInFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�Ҳ����ļ���" << filename << std::endl;
        return 0;
    }

    int lines = 0;
    std::string line;
    while (std::getline(file, line)) {
        // �ų�����
        if (!line.empty()) { 
            lines++; }
    }

    file.close();
    return lines;
}

// �������ڵݹ�ͳ���ļ��������д����ļ�������
int countLinesInFolder(const std::string& folderPath, const std::vector<std::string>& extensions) {
    int totalLines = 0;
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) { // entry��ʾÿ�ε������صĽ����recursive_directory_iterator��������Ϊ����Ŀ¼�µ����ļ��к��ļ�
        if (entry.is_regular_file()) { // �ж��Ƿ�Ϊ�����ļ� 
            std::string extension = entry.path().extension().string(); // ��ȡ���ļ�����չ������ת��Ϊstring
            if (std::find(extensions.begin(), extensions.end(), extension) != extensions.end()) { // ������ĩβλ�ò���������ЧԪ�أ���ָ����ЧԪ�غ�һλ�����ڱ�־�����Ľ���λ��
                totalLines += countLinesInFile(entry.path().string());
            }
        }
    }
    return totalLines;
}

int main() {
    std::string folderPath;
    std::cout << "������Ŀ¼·����";
    std::getline(std::cin, folderPath);

    std::vector<std::string> extensions = { ".cpp", ".h" }; // Ĭ��ͳ�� .cpp �� .h �ļ�������
    std::cout << "��Ӷ������չ�����ÿո�����������»س�ֱ�ӽ���ͳ�ƣ�Ĭ��ͳ�� .cpp �� .h �ļ����� ";
    std::string inputExtensions;
    std::getline(std::cin, inputExtensions);
    std::istringstream iss(inputExtensions);
    std::string extension;
    while (iss >> extension) {
        extensions.push_back(extension);
    }

    int totalLines = countLinesInFolder(folderPath, extensions);
    std::cout << "���Ĵ���������Ϊ�� " << totalLines << std::endl;

    return 0;
}
