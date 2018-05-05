//
// Created by yu on 2018/4/8.
//

#ifndef DES_DES_H
#define DES_DES_H

// #include <fstream> // 表写死了不用读了
#include <bitset>
#include <vector>
#include <algorithm>

// 写在类里面好丑
// 初始置换表
const int IPTable[64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
                         62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
                         57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
                         61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
// 扩展E置换表
const int ExtenedETable[64] = {32,1,2,3,4,5,4,5,6,7,8,9,
                               8,9,10,11,12,13,12,13,14,15,16,17,
                               16,17,18,19,20,21,20,21,22,23,24,25,
                               24,25,26,27,28,29,28,29,30,31,32,1};

// S盒子 8个
const int SBox[8][64] = {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
                                 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
                                 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
                                 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
                         {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                                 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                                 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                                 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},
                         {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                                 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                                 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                                 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
                         {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                                 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                                 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                                 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
                         {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                                 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                                 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                                 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
                         {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                                 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                                 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                                 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
                         {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                                 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                                 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                                 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
                         {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                                 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                                 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                                 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};

// P盒子 1个
const int PBox[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
                      2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};

// 逆初始置换表
const int IIPTable[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
                          38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
                          36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
                          34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};

// 密钥置换PC-1表
const int PC1Table[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,
                          10,2,59,51,43,35,27,19,11,3,60,52,44,36,
                          63,55,47,39,31,23,15,7,62,54,46,38,30,22,
                          14,6,61,53,45,37,29,21,13,5,28,20,12,4};

// 密钥左移位数表
const int KeyShiftTable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

// 密钥压缩置换PC-2表
const int PC2Table[48] = {14,17,11,24,1,5,3,28,15,6,21,10,
                          23,19,12,4,26,8,16,7,27,20,13,2,
                          41,52,31,37,47,55,30,40,51,45,33,48,
                          44,49,39,56,34,53,46,42,50,36,29,32};


class DES{
public:
    DES(std::string inText, std::string k);
    std::string encrypt();
    std::string decrypt();

private:
    std::vector<std::bitset<64>> text;
    std::bitset<64> key;
    std::vector<std::bitset<48>> subKeys; // 十六个子密钥

    std::string str2binstr(std::string s);
    std::string bin2str(std::bitset<64> bin);
    void get_subkeys(); // 生成子密钥
    std::bitset<64> encrypt_iteration(std::bitset<64> intext, std::bitset<48> subKey);
    std::bitset<64> decrypt_iteration(std::bitset<64> intext, std::bitset<48> subKey);
    std::bitset<32> f_function(std::bitset<32> r, std::bitset<48> subKey);
    std::bitset<64> swapLR(std::bitset<64> before); // 左右交换

};

DES::DES(std::string inText, std::string k) {

    // 检查明文/密文是否64bit的倍数
    // 检查密钥是否56bit
    if (inText.size() % 64)
        throw "The bit number of text must be a multiple of 64.";
    if (k.size() != 56)
        throw "The bit number of key must be 56.";

/*    // 字符串转比特流字符串
    // 如果输出字符串(密文会乱码fuck)
    // 下面的64也要改
    k = str2binstr(k);
    inText = str2binstr(inText);*/

    // 密文/明文分组
    // 字符串转比特流
    for (int i = 0; i < inText.size(); i += 64) {
        std::string substr = inText.substr(i,64);
        reverse(substr.begin(), substr.end()); // bitset最低位为第一位
        text.push_back(std::bitset<64> (substr));
    }

    // 密钥
    reverse(k.begin(), k.end());
    std::bitset<56> tempKey(k);
    // 给密钥留出奇偶校验位(无论具体何值) 为了方便PC-1置换
    key.reset();
    for (int j = 0, k = 0; j < 64; j++) {
        if (j % 8 != 7) {
            key[j] = tempKey[k];
            k++;
        }
    }

    // 生成子密钥
    get_subkeys();

}

std::string DES::encrypt () {

    std::string ciphertext;

    for (int i = 0; i < text.size(); i++) {

        // 初始置换
        std::bitset<64> temp;
        for(int j = 0; j < 64; j++)
            temp[j] = text[i][IPTable[j] - 1];

        // 16轮迭代 K0-K15
        for (int it = 0; it < 16; it++)
            temp = encrypt_iteration(temp, subKeys[it]);

        // 左右交换
        temp = swapLR(temp);

        // 逆初始置换-实际是置换
        std::bitset<64> re;
        for(int k = 0; k < 64; k++)
            re[k] = temp[IIPTable[k] - 1];

        // 得到ciphertext 输出字符串 注意逆序
        ciphertext += bin2str(re);
    }

    return ciphertext;
}

std::string DES::decrypt () {

    std::string plaintext;

    for (int i = 0; i < text.size(); i++) {

        // 真·逆逆初始置换
        std::bitset<64> temp;
        for(int j = 0; j < 64; j++)
            temp[IIPTable[j] - 1] = text[i][j];

        // 左右交换
        temp = swapLR(temp);

        // 16轮迭代 K15-K0
        for (int it = 15; it >= 0; it--)
            temp = decrypt_iteration(temp, subKeys[it]);

        // 真·逆初始置换
        std::bitset<64> re;
        for(int k = 0; k < 64; k++)
            re[IPTable[k] - 1] = temp[k];

        // 得到plaintext 输出字符串 注意逆序
        plaintext += bin2str(re);
    }

    return plaintext;
}


/*void DES::read_tables(int arr[], int len, std::ifstream &in) {

    int temp, i = 0;
    while(in >> temp && i < len) {
        arr[i] = temp;
        i++;
    }

}*/

/*std::string DES::str2binstr(std::string s) {

    std::string re;

    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        for(int j = 7; j >= 0; j--) {
            if (ch & 1 << j)
                re += "1";
            else
                re += "0";
        }
    }

    return re;

}*/

std::string DES::bin2str(std::bitset<64> bin) {

    std::string s = bin.to_string();
    reverse(s.begin(), s.end());
    return s;

    // 转字符会乱码, 乱码没法做解密的输入
/*    std::string re, s = bin.to_string();
    reverse(s.begin(), s.end());

    for (int i = 0; i < 64; i += 8) {
        std::string substr = s.substr(i, 8);
        re = re + char(std::bitset<8>(substr).to_ulong()); // 不可以写+=
    }

    return re;*/
}

void DES::get_subkeys() {

    // PC-1置换
    // 注意这个置换表的内容是1~63,没有8的倍数
    std::bitset<56> tempKey;
    for (int i = 0; i < 56; i++) {
        tempKey[i] = key[PC1Table[i] - 1];
    }

    // 分成keyC keyD
    std::bitset<28> keyC, keyD;
    for (int i = 0; i < 28; i++) {
        keyC[i] = tempKey[i];
        keyD[i] = tempKey[i + 28];
    }

    // 循环左移位生成十六个子密钥
    // 鉴于bitset的尿性 这里是右移
    for (int i = 0; i < 16; i++) {

        int step = KeyShiftTable[i];
        while(step--) {

            int overloadbit = keyC[0];
            keyC >>= 1;
            keyC[27] = overloadbit;

            overloadbit = keyD[0];
            keyD >>= 1;
            keyD[27] = overloadbit;
        }
        // 合并 keyC keyD
        std::bitset<56> tempSubKey;
        for (int j = 0; j < 28; j++) {
            tempSubKey[j] = keyC[j];
            tempSubKey[j + 28] = keyD[j];
        }

        // PC-2置换 56bit变48bit
        std::bitset<48> subKey;
        for (int k = 0; k < 48; k++)
            subKey[k] = tempSubKey[PC2Table[k] - 1];

        // 生成一个子密钥啦
        subKeys.push_back(subKey);

    }

}

std::bitset<64> DES::encrypt_iteration(std::bitset<64> intext, std::bitset<48> subKey) {

    std::bitset<64> re;
    std::bitset<32> r, l, foutput;

    for (int i = 0; i < 32; i++) {
        l[i] = intext[i]; // L(i-1)
        r[i] = intext[i + 32]; // R(i-1)
        re[i] = intext[i + 32]; // R(i-1)成为L(i)
    }

    // f函数
    foutput = f_function(r, subKey);

    // f函数输出与L(i-1)做异或
    foutput = l ^ foutput;

    // 拼接R(i)
    for (int j = 0; j < 32; j++)
        re[j + 32] = foutput[j];

    return re;

}

std::bitset<64> DES::decrypt_iteration(std::bitset<64> intext, std::bitset<48> subKey) {


    std::bitset<64> re;
    std::bitset<32> r, l, foutput;

    for (int i = 0; i < 32; i++) {
        l[i] = intext[i]; // L(i)
        r[i] = intext[i + 32]; // R(i)
        re[i + 32] = intext[i]; // L(i)成为R(i-1)
    }

    // R(i-1)即L(i),与subKey为f函数输入
    foutput = f_function(l, subKey);

    // L(i-1)为R(i)与foutput异或
    foutput = foutput ^ r;

    // 拼接R(i)
    for (int j = 0; j < 32; j++)
        re[j] = foutput[j];

    return re;

}

std::bitset<32> DES::f_function(std::bitset<32> r, std::bitset<48> subKey) {

    // 扩展置换
    std::bitset<48> extended;
    for (int j = 0; j < 48; j++)
        extended[j] = r[ExtenedETable[j] - 1];

    // 与子密钥进行异或
    extended = extended ^ subKey;

    // 可怕的8个S盒子
    // 又换成32bit
    std::bitset<32> soutput, re;
    for (int k = 0; k < 8; k++) {
        int row = 2 * extended[6 * k] + extended[6 * k + 5];
        int col = 8 * extended[6 * k + 1] + 4 * extended[6 * k + 2] + 2 * extended[6 * k + 3] + extended[6 * k + 4];
        int pos = row * 16 + col;

        int val = SBox[k][pos];
        std::bitset<4> v(val);
        for (int m = 0; m < 4; m++)
        soutput[4 * k + m] = v[3 - m]; // 应该反着来
    }

    // P盒子做置换
    for (int n = 0; n < 32; n++)
        re[n] = soutput[PBox[n] - 1];

    return re;
}


std::bitset<64> DES::swapLR(std::bitset<64> before) {

    std::string s = before.to_string();
    s = s.substr(32, 32) + s.substr(0, 32);

    return std::bitset<64>(s);
}


/*void DES::permutation (const int before[]&, int after[]&, const int table[], int len) {

    for(int i = 0; i < len; i++)
        after[i] = before[table[i] - 1];

}

void DES::inverse_permutation (const int before[]&, int after[]&, const int table[], int len)  {

    for (int i = 0; i < len; i++)
        after[table[i] - 1] = before[i]; // 即使after数组长度小于table也是可以的

}*/

#endif //DES_DES_H