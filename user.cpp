#pragma once
#include "user.h"

User::User() {
	strcpy_s(userName, 32, "");
	strcpy_s(realName, 64, "");
	strcpy_s(tel, 17, "");
	strcpy_s(address, 256, "");
	strcpy_s(password, 17, "");
	AccBalance = 0;
	status = -1;
	strcpy_s(UUID, 17, create_uuid().c_str());
}

User::User(const User& t) {
	strcpy_s(userName, 32, t.userName);
	strcpy_s(realName, 64, t.realName);
	strcpy_s(tel, 17, t.tel);
	strcpy_s(address, 256, t.address);
	strcpy_s(password, 17, t.password);
	AccBalance = t.AccBalance;
	status = t.status;
	strcpy_s(UUID, 17, t.UUID);
}

User::User(
	string usrN,
	string pwd,
	string realN,
	string telN,
	string addr
) {
	strcpy_s(userName, 32, usrN.c_str());
	strcpy_s(password, 17, pwd.c_str());
	strcpy_s(realName, 64, realN.c_str());
	strcpy_s(tel, 17, telN.c_str());
	strcpy_s(address, 256, addr.c_str());
	AccBalance = 0;
	status = 0;
	strcpy_s(UUID, 17, create_uuid().c_str());
}

int User::changePwd(string pwd) {
	int res = checkPwd(pwd,0);//
	if (res == 0) {
		strcpy_s(password, 17, pwd.c_str()); 
	}
	return res;
}


int User::charge(double amount) {
	if (amount > 0) {
		AccBalance += amount;
		return 0;
	}
	else {
		return -1;
	}
}