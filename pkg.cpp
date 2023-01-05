#pragma once
#include "pkg.h"

Package::Package() {
	strcpy_s(from, 32, "");
	strcpy_s(fAddress, 256, "");

	strcpy_s(to, 32, "");
	strcpy_s(tAddress, 256,"");

	strcpy_s(sendTime, 20, "");
	strcpy_s(rcvTime, 20, "");

	strcpy_s(description, 256, "NULL");
	strcpy_s(UUID, 17, "0000000000000000");
	type = -1;
	status = -1;
}

Package::Package(User& fromUsr, User& toUsr, int t, std::string describe) {
	status = 0;
	type = t;
	strcpy_s(from, 32, fromUsr.userName);
	strcpy_s(fAddress, 256, fromUsr.address);

	strcpy_s(to, 32, toUsr.userName);
	strcpy_s(tAddress, 256, toUsr.address);

	strcpy_s(sendTime, 20, getRT().c_str());
	strcpy_s(rcvTime, 20, "");

	strcpy_s(description, 256, describe.c_str());
	strcpy_s(UUID, 17, create_uuid().c_str());

}

int Package::pack(User& fromUsr, User& toUsr, int t, std::string describe) {
	status = 0;
	type = t;
	strcpy_s(from, 32, fromUsr.userName);
	strcpy_s(fAddress, 256, fromUsr.address);

	strcpy_s(to, 32, toUsr.userName);
	strcpy_s(tAddress, 256, toUsr.address);

	strcpy_s(sendTime, 20, getRT().c_str());
	strcpy_s(rcvTime, 20, "");

	strcpy_s(description, 256, describe.c_str());
	strcpy_s(UUID, 17, create_uuid().c_str());
	return 0;
}

int Package::receiption() {
	if (status == 0) {
		status = 1;
		return 0;
	}
	else { return -1; }
}