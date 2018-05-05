//
// Created by yu on 2018/4/8.
//

// 对二进制流进行加密/解密
// 输入文件 DESInput.txt && DESKey.txt
// DESInput.txt 第1行:E/D 表示加密/解密 第二行:明文/密文
// 输出文件 DESOutput.txt

#include <iostream>
#include <fstream>
#include "DES.h"

using namespace std;

int main () {

    // 读数据
    string inText, outText, key;
    char command;

    ifstream inFile1("DESInput.txt");
    if(!inFile1) {
        cout << "无法打开输入文件" << endl;
        return 1;
    }
    inFile1 >> command; // D 解密 E 加密
    inFile1 >> inText;

    ifstream inFile2("DESKey.txt");
    if(!inFile2) {
        cout << "无法打开输入文件" << endl;
        return 1;
    }
    inFile2 >> key;

    inFile1.close();
    inFile2.close();

    // 解析数据
    if (command != 'D' and command != 'E') {
        cout << "错误指令" << endl;
        return 1;
    }


    try {
        DES D(inText, key);
        if (command == 'D')
            outText = D.decrypt();
        else if (command == 'E')
            outText = D.encrypt();

        // 写数据
        ofstream outFile("DESOutput.txt");
        if(!outFile) {
            cout << "无法打开输出文件" << endl;
            return 1;
        }

        outFile << outText << endl;
        outFile.close();
    }
    catch(string s) {
        cerr << s << endl;
        return 1;
    }

    return 0;

}