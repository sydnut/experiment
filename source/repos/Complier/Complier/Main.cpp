#include<iostream>
#include<string>
#include<fstream>
#include"Lexer.h"
#include<map>
#include"Parser.h"
using namespace std;




int main() {
    // 文件名
    const char* filename = "test.txt";
    // 打开文件
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return 1;
    }
    // 确定文件大小
    file.seekg(0, std::ios::end); // 移动到文件末尾
    std::streamsize size = file.tellg(); // 获取当前位置，也就是文件大小
    file.seekg(0, std::ios::beg); // 移动回文件开始位置
    char* buffer = new char[size + 1];

    // 读取文件内容
    if (file.read(buffer, size)) {
        buffer[size] = '\0';
        cout << "以下是文件原文:" << endl;
        for (int i = 0; i <= size; i++) {
            cout << buffer[i];
        }
        cout << endl << "语法分析结果：" << endl;








        
        Parser parser(buffer, size);
        parser.start();









    }
    else {
        std::cerr << "读取文件失败" << std::endl;
        delete[] buffer;
        return 1;
    }
    file.close();
    delete[] buffer;

    return 0;
}