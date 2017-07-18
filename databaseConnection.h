#ifndef HDM_DATABASE_CONNECTION
#define HDM_DATABASE_CONNECTION


#include<qstring.h>
#include<qsqldatabase.h>
#include<qmessagebox.h>

class DatabaseConnection
{
	private:
	DatabaseConnection();
	bool makeConnection();
	void breakConnection();

	QSqlDatabase * db;

	QString username;
	QString server;
	QString password;
	QString database;

	public:
	static void setUserName(QString s);
	static void setServer(QString s);
	static void setPassword(QString s);
	static void setDatabase(QString s);

	static bool instantiate();
	static bool  connect();
	static void  disconnect();

	static DatabaseConnection * _databaseConnection;
	static bool instantiated;
	static bool connected;
};

#endif
