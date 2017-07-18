#ifndef HDM_DOWNLOAD_H
#define HDM_DOWNLOAD_H

#include<iostream>
//#include<qmainwindow.h>
#include<qtextstream.h>
#include<qhttp.h>
//#include<qobject.h>
#include<qstring.h>
#include<qstringlist.h>
#include<qfile.h>
#include<qdom.h>
#include<qapplication.h>
//#include<qtextedit.h>
//#include<qmessagebox.h>
//#include"xmlreader.h"
#include"hdm.h"
#include"passwordDialog.h"

class downloader : public QObject
{
	Q_OBJECT
	public:
	downloader(QObject *parent = 0, const char *name = 0);
	void exec();
	static void setHostname(QString hstname){hostname = hstname;}
	static QString hostname;

	void setloginName(QString str){loginName = str;}
	void setloginPassword(QString str){loginPassword = str;}

	private slots:
	void downloadFinished(bool error);
	void recieveResponseHeader(const QHttpResponseHeader &resp);

	private:
	QHttp http;
	QHttpRequestHeader request;
	QHttpResponseHeader response;
	QString CookieString;
	QFile file;
	QString filename;
	QString text;
	//QTextEdit *textedit;

	enum {
		fetchServer,
		login,
		fetchPlayers
	} downloadAction;

	void parselogin();
	void parseserver();
	void parsePlayers();

	QString loginName;
	QString loginPassword;
	QString getStr;
};

#endif

