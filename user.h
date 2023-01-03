#pragma once

#ifndef USR
#define USR

#include <string>
#include "etFx.h"

using namespace std;

class User {
public:
	char userName[32];	//用户名
	char realName[64];	//姓名
	char tel[15];		//电话号码
	char address[256];	//地址
	char password[17];	//密码
	double AccBalance;	//余额

	int status;			//0：正常
	char UUID[17]; 		//16 位+'\0'

	User();
	User(const User& t);
	User(
		string usrN,
		string realN,
		string telN,
		string addr,
		string pwd
	);

	int changePwd(string);
	int charge(double);

};

#endif