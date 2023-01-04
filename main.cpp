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
	int i=Manager.setUsrFile("./data/usr.dat");
	int j=Manager.setPkgFile("./data/pkg.dat");
	//测试
	cout << "isFileExist? usr: " << i << ", pkg: " << j << endl;
	User test(
		"Xiaoming",
		"QWER1234asdf",
		u8"李小明",
		u8"+86 13000000000",
		u8"北京市海淀区信息路48"
	);

	cout <<u8"Ret:AddUsr 下标（-2表示已存在）：" << Manager.addUsr(test) << endl;

	cout << u8"UserFound 下标：" << Manager.checkExist("Xiaoming") << endl;
	cout << u8"UserFound 下标：" << Manager.checkExist("0721") << endl;

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