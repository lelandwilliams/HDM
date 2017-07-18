//#include "hdm.h"
#include "xmldownload.h"
#include<qapplication.h>
#include<iostream>
#include<passwordDialog.h>

int main(int argc, char *argv[])
{
	QApplication a( argc, argv );
	HDM::createConnection();
	downloader d;
	/*PasswordDialog * pDlg = new PasswordDialog();
	if(pDlg->exec() == QDialog::Accepted)
	{
		//d.setloginName("xxxxx");
		//d.setloginPassword("xxxxxx");
		d.setloginName(pDlg->password());
		d.setloginPassword(pDlg->loginname());
//		std::cout << "executing downloader" << std::endl;
		d.exec();
	}*/
	d.exec();
	//else qApp->quit();
	//HDM::parsePlayers();

	return(a.exec());
}


