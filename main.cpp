#include <iostream>

#include <direct.h>
#include "DataManager.h"

#include "json/json.h"
#include "httplib.h"
#include "windows.h"

#include "etFx.h"

using namespace std;
using namespace httplib;

//#include "getRT.h"
int main() {
	//编码调整为utf-8
	SetConsoleOutputCP(65001);

	//数据存储路径检测
	if (_access("./data", 0) != 0) {
		if (_mkdir("./data")){
			cerr << u8"DATA PATH ERROR!\t" << endl;
		}
	}
	//数据管理器初始化
	DataManager Manager;
	Manager.setUsrFile("./data/usr.dat");
	Manager.setPkgFile("./data/pkg.dat");


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

	/*

	//http server配置
	if (_access("./webpages", 0) != 0) 
		{cerr << u8"网页文件缺失\t" << endl;}
	//网页服务端初始化
	Server svr;
	svr.set_base_dir("./webpages");

	*/

	system("pause");
	return 0;
}