#include"hdm.h"

int HDM::last_player_id = 0; // what is this for ?

void HDM::createConnection()
{
/*
	QSqlDatabase * db;
	db=QSqlDatabase::addDatabase("QMYSQL3");
	db->setDatabaseName("hattrick");
	db->setUserName("hattrick");
	db->setHostName("localhost");
	if( !db->open() )
	{
		 QMessageBox::critical(0, "Database Connection Error", db->lastError().text() );
		 qApp->quit();
	}
*/
}

void HDM::create_tmp_table()
{
	QSqlQuery q;
	QString statement;

	statement = " DROP TEMPORARY TABLE players_tmp IF EXISTS";
	if(!q.exec(statement))
		SqlBomb("HDM::create_tmp_table()","Error deleting Temp Table");

	statement = " CREATE TEMPORARY TABLE players_tmp LIKE players";
	if(!q.exec(statement))
		SqlBomb("HDM::create_tmp_table()","Error creating table players_tmp");
}

void HDM::startTransaction()
{
	QSqlQuery q;
	q.exec("START TRANSACTION");
}

void HDM::commit()
{
	QSqlQuery q;
	q.exec("COMMIT");
}

void HDM::rollback()
{
	QSqlQuery q;
	q.exec("ROLLBACK");
}

void HDM::SqlBomb(QString position, QString Description)
{
	QString s = QSqlDatabase::database()->lastError().databaseText();
	Description = Description + "\n\n\n" + s;
	QMessageBox::critical(0, position, Description);

	rollback();

	qApp->quit();
}

void HDM::parsePlayers()
{
	bool debug = false; // set this to false when you want 
			   // the program to actually fill
			   // the table


	QDomDocument 	doc("Players");
	QFile		file("players.xml");
	QString 	sql=NULL;
	QString 	table="PlayerTMP";
	QSqlQuery 	query;
	int		curID=0;
	int		playerIdx=0;


///////////////////////////////////////////
//
//	Open the file, and Read its
//	info into doc
//
//	Then close file
//////////////////////////////////////////

	if(!file.open(IO_ReadOnly))
		return;

	if(!doc.setContent(&file))
	{
		file.close();
		return;
	}
	file.close();

/////////////////////////////////////////////
//
//	Create a new table to hold the new
//	values
//
/////////////////////////////////////////////

	if(!debug)
	{
		sql = QString("DROP TABLE IF EXISTS %1 ") .arg(table);
		if(!query.exec(sql))
			SqlBomb("HDM::parsePlayers()","Could not execute Drop Table");
		sql = QString("CREATE  TABLE %1 LIKE players") .arg(table);
		if(!query.exec(sql))
			SqlBomb("HDM::parsePlayers()","Could not execute Create Table");
	}

////////////////////////////////////////////
//
//	Now Parse the XML file and add
//	values to the Database
//
///////////////////////////////////////////


	QDomNodeList nodeList = doc.elementsByTagName("PlayerList"); //	Get a list of all Nodes tagged PlayerList
									   // 	(should only be 1 Node named this in file)

	if(nodeList.count() !=1)
		HDM::SqlBomb("parsePlayers","Incorrect Number of PlayerList nodes");

	QDomNode playerListNode = nodeList.item(0);
	QDomElement e = playerListNode.toElement();
	if(e.isNull())
		QMessageBox::critical(0, "parsePlayers", "PlayerListNode is not an Element");
	if(e.tagName() != "PlayerList")
		QMessageBox::critical(0, "parsePlayers", "PlayerListNode is not a PlayerList");
	if(debug)
	{
		std::cout << "(debug) Number of Player Nodes = " << playerListNode.toElement().attributeNode("Count").value() << std::endl;
	}

	QDomNode playerNode = playerListNode.firstChild();
	playerIdx = 0;

	while(!playerNode.isNull())
	{
		if(debug)
			std::cout << "(debug) PlayerNum = " << playerIdx << std::endl;
		if(!playerNode.isElement())
			QMessageBox::critical(0, "parsePlayers", "PlayerNode is not a Element");
		if(playerNode.toElement().tagName() != "Player")
			QMessageBox::critical(0, "parsePlayers", "PlayerNode tagname is not Player");
		QDomNode playerQualityNode = playerNode.firstChild();
		while(!playerQualityNode.isNull())
		{
			QString quality = playerQualityNode.toElement().tagName();
			if(!playerQualityNode.firstChild().toText().isNull())
			{
				QString value = playerQualityNode.firstChild().toText().data();
				if(xmlsqlmap::contains(quality))
				{
					quality = xmlsqlmap::translate(quality);
						if(quality !="")
							if(debug)
								std::cout << "\t" << quality << " = " << value << std::endl;
							else
							{
								if(quality == "ID")
								{
									curID=value.toInt();
									sql=QString("INSERT INTO %1 (ID) VALUES(%2)")
											.arg(table)
											.arg(value);
									if(!query.exec(sql))
										HDM::SqlBomb("HDM::parsePlayers()","Cannot Insert ID");
								}
								else
								{
									sql = QString("UPDATE %1 SET %2 = '%3' WHERE ID = %4")
											.arg(table)
											.arg(quality)
											 .arg(value)
											 .arg(curID) ;
									if(!query.exec(sql))
										HDM::SqlBomb("HDM::parsePlayers()","Cannot Insert Player Quality");
								}
							}
				}
			}
			playerQualityNode = playerQualityNode.nextSibling();
		}
		playerIdx++;
		playerNode = playerNode.nextSibling();
	}
		
	/*for(uint PlayerNum = 0;PlayerNum < PlayerNodeList.count(); PlayerNum++)
	{
		if(debug)
		{
			std::cout << "(debug) PlayerNum = " << PlayerNum << std::endl;
		}

		QDomNode PlayerNode = PlayerNodeList.item(PlayerNum);
		for(QDomNode node = PlayerNode.firstChild(); !node.isNull(); node.nextSibling())
		{
			if(node.isElement())
			{
				QDomElement playerQuality = node.toElement();
				if( xmlsqlmap::contains(playerQuality.tagName()) && (xmlsqlmap::translate(playerQuality.tagName()) !="" ))
				{
					QString quality =xmlsqlmap::translate(playerQuality.tagName()); 
					QString value = playerQuality.text();

					if(quality = "ID")
					{
						curID = value.toInt();

						if(debug)
							std::cout << std::endl << "(debug) PlayerID = " << curID << std::endl;
						else
						{
							sql=QString("INSERT INTO %1 ('ID') VALUES(%2)")
									.arg(table)
									.arg(value);

							if(!query.exec(sql))
								HDM::SqlBomb("HDM::parsePlayers()","Cannot Insert ID");
						}
					}
					else
					{
						if(debug)
							std::cout << "\t(debug) " << quality <<" = " << value << std::endl;
						else
						{
							sql = QString("INSERT INTO %1 (%2) VALUES(%3) WHERE ID = %4")
									.arg(table)
									.arg(quality)
									 .arg(value)
									 .arg(curID) ;

							if(!query.exec(sql))
								HDM::SqlBomb("HDM::parsePlayers()","Cannot Insert Player Quality");
						}
					}
				}
			}
		}
	}*/
}

