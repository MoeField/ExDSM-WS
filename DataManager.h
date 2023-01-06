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
	//初始化储存文件
	int setUsrFile(string);
	int setPkgFile(string);
	int setAdminFile(string);
	//查找
	int checkExistUsr(string);//根据用户名
	int checkExistPkg(string);//uuid

	int verifyUsr(string, string);
	int changePwd(string, string);

	int addUsr(User&);//添加新用户
	int charge(string, double);//充钱

	Json::Value getUsrData(string);//获取用户信息

	int _addPkg(Package&);
	int addPkg(User&, User&, double, int, string);
	Json::Value getPkgData(string, char);

	int receiptPkg(string, string);//uuid

	map<string, int> UsrMap; 
	map<string, int> PkgMap;// uuid->下标
	map<string, vector<int> > PkgFromMap;
	map<string, vector<int> > PkgToMap;
};


