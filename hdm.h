#ifndef HDM_H
#define HDM_H

#include<qapplication.h>
#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qdom.h>
#include<xmlsqlmap.h>
#include<qsqlquery.h>
#include<qstring.h>
#include<qfile.h>



class HDM
{

	public:

	static void createConnection();
	static void rollback();
	static void commit();
	static void SqlBomb(QString position, QString Description);
	static void startTransaction();
	static void create_tmp_table();
	static void parsePlayers();

	static int last_player_id;
};

#endif 
