#pragma once

#include <fstream>
#include <string>

#include <assert.h>

#include "etFx.h"
#include "user.h"
#include "pkg.h"

#include <vector>
#include <map>

using namespace std;

class DataManager
{
private:
	fstream UsrFile;
	fstream PkgFile;

	vector<User> users;
	map<string, int> UsrMap;

	vector<Package> packages;
	map<string, vector<int> > PkgMap;
	map<string, vector<int> > PkgFromMap;
	map<string, vector<int> > PkgToMap;

public:
	int setUsrFile(string);
	int setPkgFile(string);

	int checkExist(string);
	int verifyUsr(string, string);
	
	int addUsr(User&);
	int charge(double);



	int addPkg();
	int receiptPkg();

};

