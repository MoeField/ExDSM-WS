#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include "etFx.h"
#include "user.h"
#include "pkg.h"

#include "json/json.h"
#include <vector>
#include <map>

using namespace std;

class Admin {
public:
	Admin() {
		ballance = 0;
		strcpy_s(pwd, 17, "");
	}
	char pwd[17];
	double ballance;
};

class DataManager {
public:
	fstream UsrFile;
	fstream PkgFile;
	fstream AdminFile;

	Admin admin;
	vector<User> users;
	vector<Package> packages;

	DataManager();
	DataManager(string, string);
	~DataManager();

	int setUsrFile(string);
	int setPkgFile(string);
	int setAdminFile(string);

	int checkExistUsr(string);
	int checkExistPkg(string);

	int verifyUsr(string, string);
	int changePwd(string, string);

	int addUsr(User&);
	int charge(string, double);

	Json::Value getUsrData(string);

	int _addPkg(Package&);
	int addPkg(User&, User&, double, int, string);
	Json::Value getPkgData(string, char);

	int receiptPkg(string, string);//uuid

	map<string, int> UsrMap;
	map<string, int> PkgMap;
	map<string, vector<int> > PkgFromMap;
	map<string, vector<int> > PkgToMap;
};


