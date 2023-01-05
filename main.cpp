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
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	int id = Manager.verifyUsr(usrName, pwd);

	switch (id) {
	case 0:rsp.status = 200; break;
	case -403:rsp.status = 403; break;
	case -404:rsp.status = 404; break;
	default:rsp.status = 500; break;
	}
}

void regist(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd, realName, tel, address;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	realName = UrlDecode(req.get_param_value("realName").c_str());
	tel = UrlDecode(req.get_param_value("tel").c_str());
	address = UrlDecode(req.get_param_value("address").c_str());

	if (usrName.length() < 3 || pwd.length() < 6) {
		rsp.status = 400;
		return;
	}
	int id = Manager.checkExistUsr(usrName);
	if (id == -404) {//如果未找到同用户名的用户
		User temp(usrName, pwd, realName, tel, address);
		Manager.addUsr(temp);
		rsp.status = 200;
	}
	else if (id >= 0) { rsp.status = 403; }
	else { rsp.status = 500; }
}

void sendPkg(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd, to, describe;
	double amount; int type;

	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	to = req.get_param_value("to").c_str();
	string2num(req.get_param_value("type").c_str(), type);
	string2num(req.get_param_value("amount").c_str(), amount);
	describe = UrlDecode(req.get_param_value("describe").c_str());

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
			case -400:rsp.status = 400; break;
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
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	string usrName, pwd;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
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
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	string usrName, pwd;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
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

void checkPkgInUid(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	string uuid;
	uuid = req.get_param_value("usrName").c_str();

	int id = Manager.checkExistPkg(uuid);
	if (id >= 0) {
		string res = Manager.getPkgData(uuid, 'u').toStyledString();
		//cout << res << endl;
		rsp.set_header("Content-Type", "application/json;charset=UTF-8");
		rsp.set_content(res, "application/json;charset=UTF-8");
		rsp.status = 200;
	}
	else { rsp.status = 404; }
}

void receiption(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd, pkgUid;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	pkgUid = req.get_param_value("uuid").c_str();

	int id = Manager.verifyUsr(usrName, pwd);
	if (id == 0) {
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
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd;
	double amount;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	string2num(req.get_param_value("amount").c_str(), amount);
	cout << amount << endl;
	int id = Manager.verifyUsr(usrName, pwd);
	cout << id << endl;
	if (id == 0) {
		int res = Manager.charge(usrName, amount);
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
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	int id = Manager.verifyUsr(usrName, pwd);
	Json::Value j;
	if (id == 0) {
		int seq = Manager.checkExistUsr(usrName);
		j["ballance"] = Manager.users[seq].AccBalance;
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
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd, newPwd;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	newPwd = UrlDecode(req.get_param_value("newPassword").c_str());
	int id = Manager.verifyUsr(usrName, pwd);
	if (id == 0) {
		int res = Manager.changePwd(usrName, newPwd);
		if (res == 0) { rsp.status = 200; }
		else { rsp.status = 400; }
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
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string usrName, pwd;
	usrName = UrlDecode(req.get_param_value("usrName").c_str());
	pwd = UrlDecode(req.get_param_value("password").c_str());
	int id = Manager.verifyUsr(usrName, pwd);
	string res;
	if (id == 0) {
		res = Manager.getUsrData(usrName).toStyledString();
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

//adminApi
void adminLogin(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string pwd;
	pwd = UrlDecode(req.get_param_value("password").c_str());
	if (strcmp(pwd.c_str(), Manager.admin.pwd) == 0) {
		rsp.status = 200;
	}
	else { rsp.status = 401; }
}

void adminBallance(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string pwd;
	pwd = UrlDecode(req.get_param_value("password").c_str());
	Json::Value j;
	if (strcmp(pwd.c_str(), Manager.admin.pwd) == 0) {
		j["ballance"] = Manager.admin.ballance;
		string res = j.toStyledString();
		rsp.set_header("Content-Type", "application/json;charset=UTF-8");
		rsp.set_content(res, "application/json;charset=UTF-8");
		rsp.status = 200;
	}
	else { rsp.status = 401; }
}

void adminGetUsrData(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string pwd;
	pwd = UrlDecode(req.get_param_value("password").c_str());
	string res;
	if (strcmp(pwd.c_str(), Manager.admin.pwd) == 0) {
		res = Manager.getUsrData("admin").toStyledString();
		rsp.set_header("Content-Type", "application/json;charset=UTF-8");
		rsp.set_content(res, "application/json;charset=UTF-8");
		rsp.status = 200;
	}
	else { rsp.status = 403; }
}

void adminGetPkgData(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	string pwd;
	pwd = UrlDecode(req.get_param_value("password").c_str());
	string res;
	if (strcmp(pwd.c_str(), Manager.admin.pwd) == 0) {
		res = Manager.getPkgData("admin", 'a').toStyledString();
		rsp.set_header("Content-Type", "application/json;charset=UTF-8");
		rsp.set_content(res, "application/json;charset=UTF-8");
		rsp.status = 200;
	}
	else { rsp.status = 403; }
}

void adminChangePwd(const Request& req, Response& rsp) {
	cout << "httplib server recv a req:" << req.path << "\t" << UrlDecode(req.body.c_str()) << endl;
	//处理请求
	string pwd, nPwd;
	pwd = UrlDecode(req.get_param_value("password").c_str());
	nPwd = UrlDecode(req.get_param_value("newPassword").c_str());
	if (strcmp(pwd.c_str(), Manager.admin.pwd) == 0) {
		int res = Manager.changePwd("admin", nPwd);
		if (res == 0) { rsp.status = 200; }
		else { rsp.status = 400; }
	}
	else { rsp.status = 401; }
}

//-------------------------------------------------------------------------------------------------------------------------

int main() {
	//编码调整为utf-8
	SetConsoleOutputCP(65001);

	//数据存储路径检测
	if (_access("./data", 0) != 0) {
		cout << "Data Path Not Exist, Try Creat New One." << endl;
		if (_mkdir("./data")) {
			cerr << u8"DATA PATH ERROR!\t" << endl;
		}
	}
	//数据管理器初始化

	Manager.setUsrFile("./data/usr.dat");
	Manager.setPkgFile("./data/pkg.dat");
	Manager.setAdminFile("./data/admin.dat");

	cout << u8"DataBase Found.\n" << endl;

	//http server配置
	if (_access("./webpages", 0) != 0)
	{
		cerr << u8"网页文件缺失\t" << endl;
	}
	//网页服务端初始化
	Server svr;
	svr.set_base_dir("./webpages");
	//网页服务
	svr.Get("/", index);
	svr.Get("/index", index);

	//Api服务
	svr.Post("/api/login", login);
	svr.Post("/api/regist", regist);

	svr.Post("/api/sendPkg", sendPkg);
	svr.Post("/api/checkSent", checkSent);
	svr.Post("/api/checkPkgInUid", checkPkgInUid);
	svr.Post("/api/receiption", receiption);
	svr.Post("/api/checkRcv", checkRcv);

	svr.Post("/api/charge", charge);
	svr.Post("/api/getBallance", getBallance);
	svr.Post("/api/changePwd", changePwd);
	svr.Post("/api/getUsrData", getUsrData);

	//adminApi
	svr.Post("/adminApi/adminLogin", adminLogin);
	svr.Post("/adminApi/adminGetUsrData", adminGetUsrData);
	svr.Post("/adminApi/adminGetPkgData", adminGetPkgData);
	svr.Post("/adminApi/checkPkgInUid", checkPkgInUid);
	svr.Post("/adminApi/adminChangePwd", adminChangePwd);

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

