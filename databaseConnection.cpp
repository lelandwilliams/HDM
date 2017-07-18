#include"databaseConnection.h"


DatabaseConnection::DatabaseConnection()
{
//	instantiated = true;
}

bool DatabaseConnection::instantiate()
{
	if(!instantiated)
		_databaseConnection = new DatabaseConnection;

	if(_databaseConnection)
		return true;
	else
		return false;
}

void DatabaseConnection::setUserName(QString s)
{
	instantiated = instantiate();
	_databaseConnection->username = s;
}

void DatabaseConnection::setServer(QString s)
{
	instantiated = instantiate();

	_databaseConnection->server = s;
}

void DatabaseConnection::setDatabase(QString s)
{
	instantiated = instantiate();

	_databaseConnection->database = s;
}

void DatabaseConnection::setPassword(QString s)
{
	instantiated = instantiate();

	_databaseConnection->password = s;
}

bool DatabaseConnection::makeConnection()
{
	if(connected)
		return false;

	instantiated = instantiate();

	db=QSqlDatabase::addDatabase("QMYSQL3");
	db->setDatabaseName(database);
	db->setUserName(username);
	db->setHostName(server);
	db->setPassword(password);
	if( !db->open() )
	{
	//	 QMessageBox::critical(0, "Database Connection Error", db->lastError().text() );
		 return false;
	}

	connected = true;
	return true;
}

bool  DatabaseConnection::connect()
{
	instantiated = instantiate();

	return _databaseConnection->makeConnection();
}

void DatabaseConnection::disconnect()
{
	if(connected)
		_databaseConnection->breakConnection();
}

void DatabaseConnection::breakConnection()
{
	db->disconnect();
}

DatabaseConnection *DatabaseConnection::_databaseConnection = NULL;
bool DatabaseConnection::instantiated = false;
bool DatabaseConnection::connected = false;

