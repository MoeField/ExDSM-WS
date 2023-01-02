#pragma once

#include <sstream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <random>

#include <iostream>

using namespace std;

std::string create_uuid();
std::string combine(const char[], const char[]);
int checkPwd(string& , int);

string create_uuid()
{
    stringstream stream;
    auto random_seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 seed_engine(random_seed);
    uniform_int_distribution<size_t> random_gen;
    size_t value = random_gen(seed_engine);
    stream << hex << value;
    return stream.str();
}

string combine(const char a[], const char b[]) {
    string res = a;
    res += b;
    return res;
}

int checkPwd(string& pwd, int secureLVL = 0) {
    if (pwd.length() < 8) {
        return -11;//���볤�ȹ���
    }
    else if (pwd.length() > 16) {
        return -12;//���볤�ȹ���
    }

    int numCount = 0;//����ͳ�����ֵĸ���
    int majCount = 0;
    int minCount = 0;
    int symbCount = 0;
    for (int i = 0; i < pwd.length(); i++) //����У���ַ����� 
    {
        if (pwd[i] <= '9' && pwd[i] >= '0') { numCount++; }
        else if (pwd[i] <= 'z' && pwd[i] >= 'a') { minCount++; }
        else if (pwd[i] <= 'Z' && pwd[i] >= 'A') { majCount++; }
        else if (pwd[i] <= 32 || pwd[i] >= 127) { return -21; }//���в��Ϸ����ַ�
        else { symbCount++; }
    }
    if (!numCount) { return -20; }//û������
    if (secureLVL > 0) {
        if (!majCount) { return -31; }//û�д�д��ĸ
        if (!minCount) { return -32; }//û��Сд��ĸ
    }
    if (!(majCount + minCount)) { return -30; }//û����ĸ

    if (secureLVL > 1) {
        if (!symbCount) { return -22; }//û���������
    }
    return 0;
}