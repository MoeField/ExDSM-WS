#pragma once

#ifndef USR
#define USR

#include <string>
#include "etFx.h"

using namespace std;

class User {
public:
	char userName[32];	//�û���
	char realName[64];	//����
	char tel[15];		//�绰����
	char address[256];	//��ַ
	char password[17];	//����
	double AccBalance;	//���

	int status;			//0������
	char UUID[17]; 		//16 λ+'\0'

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