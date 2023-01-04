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
	Manager.setUsrFile("./data/usr.dat");
	Manager.setPkgFile("./data/pkg.dat");


	//����
	User test0(
		u8"Xiaoming",
		u8"QWER1234asdf",
		u8"��С��",
		u8"+86 13000000000",
		u8"�����к�������Ϣ·48"
	);

	User test1(
		u8"MIKOTTO",
		u8"ONLYmyRailGun",
		u8"��������",
		u8"+86 15000000000",
		u8"�ձ� ѧ԰����"
	);

	cout << u8"Ret:AddUsr �±꣨-2��ʾ�Ѵ��ڣ���" << Manager.addUsr(test0) << endl;
	cout << u8"Ret:AddUsr �±꣨-2��ʾ�Ѵ��ڣ���" << Manager.addUsr(test1) << endl;

	cout << u8"UserFound �±꣺" << Manager.checkExistUsr("Xiaoming") << endl;
	cout << u8"UserFound �±꣺" << Manager.checkExistUsr("MIKOTTO") << endl;
	cout << u8"UserFound �±꣺" << Manager.checkExistUsr("0721") << endl;

	cout << u8"UserVerify ��" << Manager.verifyUsr("MIKOTTO", "ONLYmyRailGun")<<endl;
	cout << u8"UserVerify ��" << Manager.verifyUsr("Xiaoming", "ONLYmyRailGun") << endl;
	cout << u8"UserVerify ��" << Manager.verifyUsr("Xiaoming", "QWER1234asdf") << endl;
	cout << u8"UserVerify ��" << Manager.verifyUsr("rrr", "xxx") << endl;


	for (int i = 0; i < 10; i++) {
		Package pk0(Manager.users[0], Manager.users[1], 1, "testpkg");
		cout << u8"Ret:AddPkg �±꣨-2��ʾ�Ѵ��ڣ���" << Manager._addPkg(pk0) << endl;
	}

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