#pragma once

#include "DataManager.h"
#include "json/json.h"

using namespace std;

DataManager::DataManager(){}

DataManager::DataManager(string usrDataName,string pkgDataName ){
	setUsrFile(usrDataName);
	setPkgFile(pkgDataName);
}

DataManager::~DataManager() {
	UsrFile.close();
	PkgFile.close();
}


int DataManager::setUsrFile(string name) {
	UsrFile.open(name, ios::in | ios::out | ios::binary);
	if (UsrFile) {
		User tmp;
		int n = 0;
		UsrFile.seekg(0, ios::beg);
		while (!UsrFile.eof()&& UsrFile.peek()!=EOF) {
			UsrFile.read((char*)&tmp, sizeof(User));
			users.push_back(tmp);
			int n = users.size() - 1;//vector下标从0开始
			UsrMap[tmp.userName] = n;
			UsrMap[tmp.UUID] = n;
		}
	}
	else{
		//UsrFile.close(); UsrFile.clear();
		cout << "usrFileNotFound,CreatNewOne." << endl;
		UsrFile.open(name, ios::out | ios::binary);
		UsrFile.close(); UsrFile.clear();
		UsrFile.open(name, ios::in | ios::out | ios::binary);
	}

	UsrFile.seekg(0);
	if (!UsrFile) {	return -1; }
	return 0;
}

int DataManager::setPkgFile(string name) {
	PkgFile.open(name, ios::in | ios::out | ios::binary);
	if (PkgFile) {
		Package tmp;
		PkgFile.seekg(0);
		while (!PkgFile.eof() && PkgFile.peek() != EOF) {
			PkgFile.read((char*)&tmp, sizeof(User));
			packages.push_back(tmp);
			int n = packages.size() - 1;//vector下标从0开始
			PkgMap[tmp.UUID].push_back(n);
			PkgFromMap[tmp.from].push_back(n);
			PkgToMap[tmp.to].push_back(n);
		}
	}
	else{
		//UsrFile.close(); UsrFile.clear();
		cout << "pkgFileNotFound,CreatNewOne." << endl;
		PkgFile.open(name, ios::out | ios::binary);
		PkgFile.close();PkgFile.clear();
		PkgFile.open(name, ios::in | ios::out | ios::binary);
	}



	PkgFile.seekg(0);
	if (!PkgFile) { return -1; }
	return 0;
}

int DataManager::checkExist(string usrName) {
	if (!UsrFile) { return -1; 	}
	map<string, int>::iterator iter;
	iter = UsrMap.find(usrName);
	if (iter == UsrMap.end()) {
		return -404;
	}
	else {
		return UsrMap[usrName];
	}
}

int DataManager::verifyUsr(string usrName, string pwd) {
	if (!UsrFile) { return -1; }
	int id = checkExist(usrName);
	if (id < 0) {
		return -404;
	}
	else {
		if (pwd == string(users[id].userName)) {//需验证
			return 0;
		}
		else {
			return -403;
		}
	}
}

int DataManager::addUsr(User& tmp) {
	if (!UsrFile) { return -1; }
	int id = checkExist(tmp.userName);
	if (id != -404) {
		return -2;
	}
	users.push_back(tmp);
	int n = users.size();
	UsrMap[tmp.userName] = n;
	UsrMap[tmp.UUID] = n;

	UsrFile.seekp(0, ios::end);
	UsrFile.write((char*)&tmp, sizeof(User));

	return 0;
}

int DataManager::charge(double amount) {
	if (!UsrFile) { return -1; }
	return 0;
}



int DataManager::addPkg() {
	return 0;
}

int DataManager::receiptPkg() {
	return 0;
}