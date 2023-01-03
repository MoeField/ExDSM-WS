#pragma once

#include "DataManager.h"
#include "json/json.h"

using namespace std;

int DataManager::setUsrFile(string name) {
	UsrFile.open(name, ios::in | ios::out | ios::binary);
	if (!UsrFile) {
		UsrFile.open(name, ios::out | ios::binary);
		UsrFile.close();
		UsrFile.open(name, ios::in | ios::out | ios::binary);
	}
	UsrFile.seekg(0, ios::end);

	User tmp;
	int n = 0;
	while (UsrFile.read((char*)&tmp, sizeof(User))) {
		users.push_back(tmp);
		int n = users.size();
		UsrMap[tmp.userName] = n;
		UsrMap[tmp.UUID] = n;
	}
	
	return 0;
}

int DataManager::setPkgFile(string pkgName) {
	PkgFile.open(pkgName, ios::in | ios::out | ios::binary);
	if (!PkgFile) {
		PkgFile.open(pkgName, ios::out | ios::binary);
		PkgFile.close();
		PkgFile.open(pkgName, ios::in | ios::out | ios::binary);
	}
	PkgFile.seekg(0, ios::end);

	Package tmp;
	int n = 0;
	while (PkgFile.read((char*)&tmp, sizeof(User))) {
		packages.push_back(tmp);
		int n = users.size();
		PkgMap[tmp.UUID].push_back(n);
		PkgFromMap[tmp.from].push_back(n);
		PkgToMap[tmp.to].push_back(n);
	}

	return 0;

}

int DataManager::checkExist(string usrName) {
	if (!UsrFile) { return -1; }
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
		if (pwd == string(users[id].userName)) {//ÐèÑéÖ¤
			return 0;
		}
		else {
			return -403;
		}
	}
}

int DataManager::addUsr(User& tmp) {
	if (!UsrFile) { return -1; }
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