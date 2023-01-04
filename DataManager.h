#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include "etFx.h"
#include "user.h"
#include "pkg.h"

#include <vector>
#include <map>

using namespace std;

class DataManager{
public:
	fstream UsrFile;
	fstream PkgFile;

	vector<User> users;
	vector<Package> packages;

	DataManager();
	DataManager(string, string);
	~DataManager();
	int setUsrFile(string);
	int setPkgFile(string);

	int checkExistUsr(string);
	int checkExistPkg(string);

	int verifyUsr(string, string);
	
	int addUsr(User&);
	int charge(double);

	int _addPkg(Package&);
	int addPkg(User&, User&, double, int, string);

	int receiptPkg(string);//uuid
private:
	map<string, int> UsrMap;
	map<string, int> PkgMap;
	map<string, vector<int> > PkgFromMap;
	map<string, vector<int> > PkgToMap;
};

