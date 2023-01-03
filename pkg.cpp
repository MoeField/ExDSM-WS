#pragma once

#include "pkg.h"


Package::Package() {
	status = -1;
}

Package::Package(User& fromUsr, User& toUsr, std::string describe) {
	status = 0;

	strcpy_s(from, 32, fromUsr.userName);
	strcpy_s(fAddress, 256, fromUsr.address);

	strcpy_s(to, 32, toUsr.userName);
	strcpy_s(tAddress, 256, toUsr.address);

	strcpy_s(description, 256, describe.c_str());
	strcpy_s(UUID, 17, create_uuid().c_str());
}

int Package::pack(User& fromUsr, User& toUsr, std::string describe) {
	status = 0;

	strcpy_s(from, 32, fromUsr.userName);
	strcpy_s(fAddress, 256, fromUsr.address);

	strcpy_s(to, 32, toUsr.userName);
	strcpy_s(tAddress, 256, toUsr.address);

	strcpy_s(description, 256, describe.c_str());
	strcpy_s(UUID, 17, create_uuid().c_str());
	return 0;
}

int Package::receipt() {
	if (status == 0) {
		status = 1;
		return 0;
	}
	else {
		return -1;
	}
}