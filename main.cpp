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
	
	SetConsoleOutputCP(65001);

	//���ݹ�������ʼ��
	if (_access("./data", 0) != 0) {
		if (_mkdir("./data")){
			cerr << u8"DATA PATH ERROR!\t" << endl;
		}
	}
	DataManager Manager;
	int i=Manager.setUsrFile("./data/usr.dat");
	int j=Manager.setPkgFile("./data/pkg.dat");
	cout << i << " " << j << endl;

	if (_access("./webpages", 0) != 0) 
		{cerr << u8"��ҳ�ļ�ȱʧ\t" << endl;}
	//��ҳ����˳�ʼ��
	Server svr;
	svr.set_base_dir("./webpages");

	system("pause");
	return 0;
}