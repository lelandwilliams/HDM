#include<iostream>
#include"hdm.h"
#include<qstring.h>
#include<qapplication.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	HDM::createConnection();
	HDM::parsePlayers();

	return 0;
}


