#include<iostream>
#include<string>
#include<fstream>
#include"Lexer.h"
#include<map>
using namespace std;
int main() {
        // �ļ���
        const char* filename = "test.txt";
        // ���ļ�
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "�޷����ļ�: " << filename << std::endl;
            return 1;
        }
        // ȷ���ļ���С
        file.seekg(0, std::ios::end); // �ƶ����ļ�ĩβ
        std::streamsize size = file.tellg(); // ��ȡ��ǰλ�ã�Ҳ�����ļ���С
        file.seekg(0, std::ios::beg); // �ƶ����ļ���ʼλ��
        char* buffer = new char[size + 1];

        // ��ȡ�ļ�����
        if (file.read(buffer, size)) {
            buffer[size] = '\0';
            cout << "�������ļ�ԭ��:" << endl;
            for (int i = 0; i <= size; i++) {
                cout << buffer[i];
            }
            cout<<endl <<"�ʷ������������ͬ����֮���ÿո�����ÿ�е�һ�����кţ���" << endl;
            Lexer instance(buffer, size);
            for (;  instance.len< size; ) {
                instance.scan();
                cout << ' ';
            }
        }
        else {
            std::cerr << "��ȡ�ļ�ʧ��" << std::endl;
            delete[] buffer;
            return 1;
        }
        file.close();
        delete[] buffer;
        
	return 0;
}