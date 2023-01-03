#pragma once
#include "etFx.h"
using namespace std;

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
        return -11;//密码长度过短
    }
    else if (pwd.length() > 16) {
        return -12;//密码长度过长
    }

    int numCount = 0;//用来统计数字的个数
    int majCount = 0;
    int minCount = 0;
    int symbCount = 0;
    for (int i = 0; i < pwd.length(); i++) //遍历校验字符数字 
    {
        if (pwd[i] <= '9' && pwd[i] >= '0') { numCount++; }
        else if (pwd[i] <= 'z' && pwd[i] >= 'a') { minCount++; }
        else if (pwd[i] <= 'Z' && pwd[i] >= 'A') { majCount++; }
        else if (pwd[i] <= 32 || pwd[i] >= 127) { return -21; }//含有不合法的字符
        else { symbCount++; }
    }
    if (!numCount) { return -20; }//没有数字
    if (secureLVL > 0) {
        if (!majCount) { return -31; }//没有大写字母
        if (!minCount) { return -32; }//没有小写字母
    }
    if (!(majCount + minCount)) { return -30; }//没有字母

    if (secureLVL > 1) {
        if (!symbCount) { return -22; }//没有特殊符号
    }
    return 0;
}

string getRT() {
    time_t now = time(NULL);
    tm* tm_t = localtime(&now);
    std::stringstream ss;
    ss << tm_t->tm_year + 1900 << "-" << tm_t->tm_mon + 1 << "-" << tm_t->tm_mday
        << " " << tm_t->tm_hour << ":" << tm_t->tm_min << ":" << tm_t->tm_sec << "\0";

    return ss.str();
}

string _getRT() {
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    //转为字符串
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    //  ss << std::put_time(std::localtime(&t), "%Y年%m月%d日%H时%M分%S秒");
    //	ss << std::put_time(std::localtime(&t), "%Y%m%d%H%M%S");
    std::string str_time = ss.str();
    return str_time;
}