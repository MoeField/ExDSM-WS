#pragma once
#include "user.h"

User::User() {
	strcpy_s(userName, 32, "");
	strcpy_s(realName, 64, "");
	strcpy_s(tel, 15, "");
	strcpy_s(address, 256, "");
	strcpy_s(password, 17, "");
	AccBalance = 0;
	status = -1;
	strcpy_s(UUID, 17, create_uuid().c_str());
}

User::User(const User& t) {
	strcpy_s(userName, 32, t.userName);
	strcpy_s(realName, 64, t.realName);
	strcpy_s(tel, 15, t.tel);
	strcpy_s(address, 256, t.address);
	strcpy_s(password, 17, t.password);
	AccBalance = t.AccBalance;
	status = t.status;
	strcpy_s(UUID, 17, t.UUID);
}

User::User(
	string usrN,
	string realN,
	string telN,
	string addr,
	string pwd
) {
	strcpy_s(userName, 32, usrN.c_str());
	strcpy_s(realName, 64, realN.c_str());
	strcpy_s(tel, 15, telN.c_str());
	strcpy_s(address, 256, addr.c_str());
	strcpy_s(password, 17, pwd.c_str());
	AccBalance = 0;
	status = 0;
	strcpy_s(UUID, 17, create_uuid().c_str());
}

int User::changePwd(string pwd) {
	strcpy_s(password, 17, pwd.c_str());
	return 0;
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