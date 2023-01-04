#pragma once

#ifndef PKG
#define PKG

#include <string>
#include "etFx.h"
#include "user.h"

class Package {
public:
	Package();
	Package(User&, User&, int, std::string);
	int pack(User&, User&, int, std::string);
	int receipt();

	char from[32];
	char fAddress[256];
	char to[32];
	char tAddress[256];

	char sendTime[20];
	char rcvTime[20];

	int type;
	char description[256];
	char UUID[17];
	int status;
};

#endif