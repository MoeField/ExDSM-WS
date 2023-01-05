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
			PkgFile.read((char*)&tmp, sizeof(Package));
			packages.push_back(tmp);
			int n = packages.size() - 1;//vector下标从0开始
			PkgMap[tmp.UUID] = n;
			PkgFromMap[tmp.from].push_back(n);
			PkgToMap[tmp.to].push_back(n);
		}
	}
	else{
		cout << "pkgFileNotFound,CreatNewOne." << endl;
		PkgFile.open(name, ios::out | ios::binary);
		PkgFile.close();PkgFile.clear();
		PkgFile.open(name, ios::in | ios::out | ios::binary);
	}

	PkgFile.seekg(0);
	if (!PkgFile) { return -1; }
	return 0;
}

int DataManager::checkExistUsr(string usrName) {
	if (!UsrFile) { return -1; 	}
	map<string, int>::iterator iter;
	iter = UsrMap.find(usrName);
	if (iter == UsrMap.end()) { return -404; }
	else { return UsrMap[usrName]; }
}

int DataManager::verifyUsr(string usrName, string pwd) {
	if (!UsrFile) { return -1; }
	int id = checkExistUsr(usrName);
	if (id < 0) { return -404; }
	else {
		if (strcmp(users[id].password, pwd.c_str()) == 0) {
			return 0;
		}
		else { return -403; }
	}
}

int DataManager::addUsr(User& tmp) {
	if (!UsrFile) { return -1; }
	int id = checkExistUsr(tmp.userName);
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

int DataManager::charge(string usr, double amount) {
	if (!UsrFile) { return -1; }
	int seq = UsrMap[usr];
	if (seq < 0) { return -404; }
	else { return users[seq].charge(amount); }
}

Json::Value DataManager::getUsrData(string usr,int conT=0) {
	Json::Value res;
	int seq = UsrMap[usr];
	if (seq >= 0) {
		if (conT != 0) {
			res["ballance"] = users[seq].AccBalance;
		}
		else {
			res["usrname"] = users[seq].userName;
			res["pwd"] = users[seq].password;
			res["realName"] = users[seq].realName;
			res["address"] = users[seq].address;
			res["tel"] = users[seq].tel;
			res["uuid"] = users[seq].UUID;
		}
	}
	return res;
}//nonFin

//包裹
int DataManager::checkExistPkg(string uuid) {
	if (!PkgFile) { return -1; }
	map<string, int>::iterator iter;
	iter = PkgMap.find(uuid);
	if (iter == PkgMap.end()) {	return -404; }
	else { return PkgMap[uuid]; }
}

int DataManager::_addPkg(Package& tmp) {
	if (!PkgFile||!UsrFile) { return -1; }
	int id = checkExistPkg(tmp.UUID);
	if (id != -404) {
		return -2;
	}
	packages.push_back(tmp);
	int n = packages.size() - 1;//vector下标从0开始
	PkgMap[tmp.UUID] = n;
	PkgFromMap[tmp.from].push_back(n);
	PkgToMap[tmp.to].push_back(n);
	PkgFile.seekp(0, ios::end);
	PkgFile.write((char*)&tmp, sizeof(Package));
	return 0;
}

int DataManager::addPkg(User& f, User& t, double amount, int type, string d) {
	if (!PkgFile || !UsrFile) { return -1; }
	if (f.AccBalance < amount * type) { return -402; }//没钱
	else {
		f.AccBalance -= amount * type;
		UsrFile.seekp(UsrMap[f.userName] * sizeof(User));

		return _addPkg(Package(f, t, type, d));
	}
}

Json::Value DataManager::getPkgData(string usr,char w) {
	Json::Value res;
	if (w == 's'|| w == 'S') {
		for (int i = 0; i < PkgFromMap[usr].size(); ++i){
			int seq = PkgFromMap[usr][i];
			Json::Value j;

			j["from"] = packages[seq].from;
			j["fAddr"] = packages[seq].fAddress;
			j["to"] = packages[seq].to;
			j["tAddr"] = packages[seq].tAddress;

			j["sendTime"] = packages[seq].sendTime;
			j["rcvTime"] = packages[seq].rcvTime;

			j["type"]= packages[seq].type;
			j["description"] = packages[seq].description;
			j["UUID"] = packages[seq].UUID;
			j["status"] = packages[seq].status;

			res.append(j);
		}
	}
	if (w == 'r'||w=='R') {
		for (int i = 0; i < PkgToMap[usr].size(); ++i) {
			int seq = PkgToMap[usr][i];
			Json::Value j;

			j["from"] = packages[seq].from;
			j["fAddr"] = packages[seq].fAddress;
			j["to"] = packages[seq].to;
			j["tAddr"] = packages[seq].tAddress;

			j["sendTime"] = packages[seq].sendTime;
			j["rcvTime"] = packages[seq].rcvTime;

			j["type"] = packages[seq].type;
			j["description"] = packages[seq].description;
			j["UUID"] = packages[seq].UUID;
			j["status"] = packages[seq].status;

			res.append(j);
		}
	}
	if (w == 'u'|| w == 'U') {
		int seq = PkgMap[usr];
		Json::Value j;

		j["from"] = packages[seq].from;
		j["fAddr"] = packages[seq].fAddress;
		j["to"] = packages[seq].to;
		j["tAddr"] = packages[seq].tAddress;

		j["sendTime"] = packages[seq].sendTime;
		j["rcvTime"] = packages[seq].rcvTime;

		j["type"] = packages[seq].type;
		j["description"] = packages[seq].description;
		j["UUID"] = packages[seq].UUID;
		j["status"] = packages[seq].status;

		res.append(j);
	}
	return res;
}

int DataManager::receiptPkg(string usr,string pkgUid) {
	int seq = PkgMap[pkgUid];
	if (seq < 0) { return -404; }
	if (strcmp(packages[seq].to, usr.c_str()) != 0) {
		return -400;
	}
	return packages[seq].receiption();
}