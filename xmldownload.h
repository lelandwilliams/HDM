#ifndef HDM_DOWNLOAD_H
#define HDM_DOWNLOAD_H

#include<iostream>
#include<qtextstream.h>
#include<qhttp.h>
#include<qstring.h>
#include<qstringlist.h>
#include<qfile.h>
#include<qdom.h>
#include<qapplication.h>
//#include"hdm.h"
#include"passwordDialog.h"

class downloader : public QObject
{
	Q_OBJECT
	public:
	downloader(QObject *parent = 0, const char *name = 0);
	void exec();
	//static void setHostname(QString hstname){hostname = hstname;}
	QString hostname;
	void setHostname(QString hstname){hostname = hstname;}
	//static QString hostname;

	void setloginName(QString str){loginName = str;}
	void setloginPassword(QString str){loginPassword = str;}

	private slots:
	void downloadFinished(bool error);
	void recieveResponseHeader(const QHttpResponseHeader &resp);

	private:
	QHttp http;
	QHttpRequestHeader request;
	QHttpResponseHeader response;
	QString cookieString;
	QStringList cookieStringList;
	QFile file;
	QString filename;
	QString text;

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
	bool debug;	// if debug is set, lots of debugging output will be shown
};

#endif

