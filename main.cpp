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
	//�������Ϊutf-8
	SetConsoleOutputCP(65001);

	//���ݴ洢·�����
	if (_access("./data", 0) != 0) {
		if (_mkdir("./data")){
			cerr << u8"DATA PATH ERROR!\t" << endl;
		}
	}
	//���ݹ�������ʼ��
	DataManager Manager;
	int i=Manager.setUsrFile("./data/usr.dat");
	int j=Manager.setPkgFile("./data/pkg.dat");
	//����
	cout << "isFileExist? usr: " << i << ", pkg: " << j << endl;
	User test(
		"Xiaoming",
		"QWER1234asdf",
		u8"��С��",
		u8"+86 13000000000",
		u8"�����к�������Ϣ·48"
	);

	cout <<u8"Ret:AddUsr �±꣨-2��ʾ�Ѵ��ڣ���" << Manager.addUsr(test) << endl;

	cout << u8"UserFound �±꣺" << Manager.checkExist("Xiaoming") << endl;
	cout << u8"UserFound �±꣺" << Manager.checkExist("0721") << endl;

	/*
	//http server����
	if (_access("./webpages", 0) != 0) 
		{cerr << u8"��ҳ�ļ�ȱʧ\t" << endl;}
	//��ҳ����˳�ʼ��
	Server svr;
	svr.set_base_dir("./webpages");
	*/

	system("pause");
	return 0;
}