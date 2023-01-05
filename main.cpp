#include <iostream>

#include <direct.h>
#include "DataManager.h"

#include "json/json.h"
#include "httplib.h"
#include "windows.h"

#include "strCoder.h"
#include "etFx.h"

using namespace std;

using namespace httplib;

DataManager Manager;

//httpServer
string getHtmlCont(string fileName) {
	ifstream in(fileName, ios::in);
	if (in) {
		istreambuf_iterator<char> beg(in), end;
		string strdata(beg, end);
		in.close();
		return strdata;
	}
	else
		return string(u8"<html><head><title>404 页面不存在</title></head><body><h1>404</h1></body></html>");
}

//页面服务
void index(const httplib::Request& req, httplib::Response& rsp) {
	cout << "httplib server recv a req:" << req.path << endl;
	rsp.set_content(getHtmlCont("./webpages/index.html"), "text/html");
	rsp.status = 200;
}


//api
void login(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	int id = Manager.verifyUsr(usrName, pwd);
	
	switch (id) {
	case 0:rsp.status = 200; break;
	case -403:rsp.status = 403; break;
	case -404:rsp.status = 404; break;
	default:rsp.status = 500; break;
	}
}

void regist(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd, realName, tel, address;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	realName = req.get_param_value("realName").c_str();
	tel = req.get_param_value("tel").c_str();
	address = req.get_param_value("address").c_str();

	int id = Manager.checkExistUsr(usrName);
	if (id == -404) {
		User temp(usrName, pwd, realName, tel, address);
		rsp.status = 200;
	}
	else if (id == 0) {rsp.status = 403;}
	else {rsp.status = 500;}
}

void sendPkg(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd, to, describe;
	double amount; int type;

	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	to = req.get_param_value("to").c_str();
	string2num(req.get_param_value("type").c_str(), type);
	string2num(req.get_param_value("amount").c_str(), amount);
	describe = req.get_param_value("address").c_str();

	int id = Manager.verifyUsr(usrName, pwd);
	if (id == 0) {
		int fId = Manager.checkExistUsr(usrName);
		int rId = Manager.checkExistUsr(to);
		int pId = Manager.addPkg(Manager.users[fId], Manager.users[rId], amount, type, describe);
		if (pId == 0) {
			rsp.status = 200;
		}
		else {
			switch (pId) {
			case -402:rsp.status = 402; break;
			case -403:rsp.status = 403; break;
			case -404:rsp.status = 404; break;
			default:rsp.status = 500; break;
			}
		}
	}
	else {
		switch (id) {
		case -403:rsp.status = 403; break;
		case -404:rsp.status = 404; break;
		default:rsp.status = 500; break;
		}
	}
}

void checkSent(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	string usrName, pwd;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	int id = Manager.verifyUsr(usrName, pwd);

	if (id == 0) {
		string res = Manager.getPkgData(usrName, 's').toStyledString();
		//cout << res << endl;
		rsp.set_header("Content-Type", "application/json;charset=UTF-8");
		rsp.set_content(res, "application/json;charset=UTF-8");
		rsp.status = 200;
	}
	else {
		switch (id) {
		case -403:rsp.status = 403; break;
		case -404:rsp.status = 404; break;
		default:rsp.status = 500; break;
		}
	}
}

void checkRcv(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	string usrName, pwd;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	int id = Manager.verifyUsr(usrName, pwd);

	if (id == 0) {
		string res = Manager.getPkgData(usrName, 'r').toStyledString();
		//cout << res << endl;
		rsp.set_header("Content-Type", "application/json;charset=UTF-8");
		rsp.set_content(res, "application/json;charset=UTF-8");
		rsp.status = 200;
	}
	else {
		switch (id) {
		case -403:rsp.status = 403; break;
		case -404:rsp.status = 404; break;
		default:rsp.status = 500; break;
		}
	}
}

void receiption(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd,pkgUid;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	pkgUid= req.get_param_value("uuid").c_str();

	int id = Manager.verifyUsr(usrName, pwd);
	if(id==0){
		int st = Manager.receiptPkg(usrName, pkgUid);
		switch (st) {
		case 0:rsp.status = 200; break;
		case -400:rsp.status = 400; break;
		case -403:rsp.status = 403; break;
		case -404:rsp.status = 404; break;
		default:rsp.status = 500; break;
		}
	}
	else {
		switch (id) {
		case -403:rsp.status = 403; break;
		case -404:rsp.status = 404; break;
		default:rsp.status = 500; break;
		}
	}
}

void charge(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd;
	double amount;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	string2num(req.get_param_value("amount").c_str(),amount);
	int id = Manager.verifyUsr(usrName, pwd);
	if (id == 0) {
		int seq = Manager.checkExistUsr(usrName);
		int res = Manager.users[seq].charge(amount);
		if (res == 0) { rsp.status = 200; }
		else { rsp.status = 403; }
	}
	else {
		switch (id) {
		case -403:rsp.status = 403; break;
		case -404:rsp.status = 404; break;
		default:rsp.status = 500; break;
		}
	}
}

void getBallance(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	int id = Manager.verifyUsr(usrName, pwd);
	Json::Value j;
	if (id == 0) {
		int seq = Manager.checkExistUsr(usrName);
		j["amount"] = Manager.users[seq].AccBalance;
	}
	string res = j.toStyledString();

	rsp.set_header("Content-Type", "application/json;charset=UTF-8");
	rsp.set_content(res, "application/json;charset=UTF-8");
	switch (id) {
	case 0:rsp.status = 200; break;
	case -403:rsp.status = 403; break;
	case -404:rsp.status = 404; break;
	default:rsp.status = 500; break;
	}
}

void changePwd(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd, newPwd;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	newPwd= req.get_param_value("newPassword").c_str();
	int id = Manager.verifyUsr(usrName, pwd);
	if (id == 0) {
		int seq = Manager.checkExistUsr(usrName);
		int res = Manager.users[seq].changePwd(newPwd);
		if (res == 0) {
			rsp.status = 200;
		}
		else {
			rsp.status = 400;
		}
	}
	else {
		switch (id) {
		case -403:rsp.status = 403; break;
		case -404:rsp.status = 404; break;
		default:rsp.status = 500; break;
		}
	}
}

void getUsrData(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << req.body.c_str() << endl;
	//处理请求
	string usrName, pwd;
	usrName = req.get_param_value("usrName").c_str();
	pwd = req.get_param_value("password").c_str();
	int id = Manager.verifyUsr(usrName, pwd);
	string res;
	if (id == 0) {
		res=Manager.getUsrData(usrName,0).toStyledString();
	}
	rsp.set_header("Content-Type", "application/json;charset=UTF-8");
	rsp.set_content(res, "application/json;charset=UTF-8");

	switch (id) {
	case 0:rsp.status = 200; break;
	case -403:rsp.status = 403; break;
	case -404:rsp.status = 404; break;
	default:rsp.status = 500; break;
	}
}


//#include "getRT.h"
int main() {
	//编码调整为utf-8
	SetConsoleOutputCP(65001);

	//数据存储路径检测
	if (_access("./data", 0) != 0) {
		cout << "Data Path Not Exist, Try Creat New One." << endl;
		if (_mkdir("./data")){
			cerr << u8"DATA PATH ERROR!\t" << endl;
		}
	}
	//数据管理器初始化
	
	int uFileGood = Manager.setUsrFile("./data/usr.dat");
	int pFileGood = Manager.setPkgFile("./data/pkg.dat");

	if (uFileGood + pFileGood < 0) {
		cerr << "FILE ERROR" << endl;
		return -1;
	}
	cout << u8"DataBase Found.\n" << endl;
/*
	//测试
	User test0(
		u8"Xiaoming",
		u8"QWER1234asdf",
		u8"李小明",
		u8"+86 13000000000",
		u8"北京市海淀区信息路48"
	);

	User test1(
		u8"MIKOTTO",
		u8"ONLYmyRailGun",
		u8"御坂美琴",
		u8"+86 15000000000",
		u8"日本 学园都市"
	);

	cout << u8"Ret:AddUsr 下标（-2表示已存在）：" << Manager.addUsr(test0) << endl;
	cout << u8"Ret:AddUsr 下标（-2表示已存在）：" << Manager.addUsr(test1) << endl;

	cout << u8"UserFound 下标：" << Manager.checkExistUsr("Xiaoming") << endl;
	cout << u8"UserFound 下标：" << Manager.checkExistUsr("MIKOTTO") << endl;
	cout << u8"UserFound 下标：" << Manager.checkExistUsr("0721") << endl;

	cout << u8"UserVerify ：" << Manager.verifyUsr("MIKOTTO", "ONLYmyRailGun")<<endl;
	cout << u8"UserVerify ：" << Manager.verifyUsr("Xiaoming", "ONLYmyRailGun") << endl;
	cout << u8"UserVerify ：" << Manager.verifyUsr("Xiaoming", "QWER1234asdf") << endl;
	cout << u8"UserVerify ：" << Manager.verifyUsr("rrr", "xxx") << endl;


	for (int i = 0; i < 10; i++) {
		Package pk0(Manager.users[0], Manager.users[1], 1, "testpkg");
		cout << u8"Ret:AddPkg 下标（-2表示已存在）：" << Manager._addPkg(pk0) << endl;
	}
*/

	//http server配置
	if (_access("./webpages", 0) != 0) 
		{cerr << u8"网页文件缺失\t" << endl;}
	//网页服务端初始化
	Server svr;
	svr.set_base_dir("./webpages");
	//网页服务
	svr.Get("/index", index);

	//Api服务
	svr.Post("/api/login", login);
	svr.Post("/api/regist", regist);

	svr.Post("/api/sendPkg", sendPkg);
	svr.Post("/api/checkSent", checkSent);
	svr.Post("/api/receiption", receiption);
	svr.Post("/api/checkRcv", checkRcv);

	svr.Post("/api/charge", charge);
	svr.Post("/api/getBallance", getBallance);
	svr.Post("/api/changePwd", changePwd);
	svr.Post("/api/getUsrData", getUsrData);



	//异常处理
	svr.set_exception_handler([](const auto& req, auto& res, std::exception_ptr ep) {
		auto fmt = "<h1>Error 500</h1><p>%s</p>";
		char buf[BUFSIZ];
		try { std::rethrow_exception(ep); }
		catch (std::exception& e) { snprintf(buf, sizeof(buf), fmt, e.what()); }
		catch (...) { snprintf(buf, sizeof(buf), fmt, "Unknown Exception"); }// See the following NOTE
		res.set_content(buf, "text/html");
		res.status = 500;
	});

	//挂载
	//svr.set_mount_point("/", "./webpages");
	//监听端口
	svr.listen("0.0.0.0", 9666);

	system("pause");
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------------
