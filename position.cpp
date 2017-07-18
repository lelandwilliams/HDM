#include"position.h"



Position::Position(int a, QString b, QWidget *parent, const char *name) : QVGroupBox(parent, name)
{
	std::cout << "Now in Position Constructor" << std::endl ;
	positionID=a;
	positionIDStr=QString::number(a);
	positionName=b;
	
	setFetchTableQuery();
	fetchTablequery+=" ORDER BY depth";
	setBuildTableQuery();
	
	setTitle(positionName);
	tableBox = new QHBox(this);
	table = new QDataTable(tableBox);
	buttonBox = new QHBox(this);
	upButton = new QPushButton("Move Up", buttonBox);
		upButton->setAutoRepeat(FALSE);
		connect(upButton, SIGNAL(clicked()), this, SLOT(up()) );
	downButton = new QPushButton("Move Down", buttonBox);
		downButton->setAutoRepeat(FALSE);
		connect(downButton, SIGNAL(clicked()), this, SLOT(down()) );
	topButton = new QPushButton("Move to Top", buttonBox);
		topButton->setAutoRepeat(FALSE);
		connect(topButton, SIGNAL(clicked()), this, SLOT(top()) );
	deleteButton = new QPushButton("Remove Player", buttonBox);
		deleteButton->setAutoRepeat(FALSE);
		connect(deleteButton, SIGNAL(clicked()), this, SLOT(remove()) );
	addButton = new QPushButton("AddPlayer", buttonBox);
	rebuildButton = new QPushButton("Rebuild Table", buttonBox);
		rebuildButton->setAutoRepeat(FALSE);
		connect(rebuildButton, SIGNAL(clicked()), this, SLOT(rebuild()) );
	cursor = new QSqlSelectCursor();

	if(! cursor->exec(fetchTablequery) )
		SqlBomb("Position A", fetchTablequery);

	if(cursor->isActive() && !cursor->size()>0)
		rebuildAssignmentsTable();


	refreshTable();
}

void Position::setFetchTableQuery()
{
	QSqlCursor q("position_order");
	q.select(("positionID = " + positionIDStr));
	QStringList fields = q.toStringList();
	orderMap map;

	while(q.next())
		for(QStringList::iterator it = fields.begin(); it != fields.end(); it++)
			if(*it != "positionID")
				if( q.value(*it).toInt() != -1 )
					map[*it] = q.value(*it).toInt();

	fetchTablequery = "SELECT p.Name ";
	
	for(int curVal = map.count(); curVal !=0; curVal--)
		for(orderMap::iterator it = map.begin(); it != map.end(); it++)
			if(it.data() == curVal)
				fetchTablequery += (" , p." + it.key());

	fetchTablequery += " FROM players p, assignments a ";
	fetchTablequery += "WHERE p.ID = a.ID AND a.positionID = ";
	fetchTablequery += positionIDStr;
}

void Position::setBuildTableQuery()
{
	QSqlCursor q("position_order");
	q.select(("positionID = " + positionIDStr));
	QStringList fields = q.toStringList();
	fields.remove("positionID");
	q.next();

	QStringList::iterator it = fields.begin();
	while(it != fields.end())
		if(q.value(*it).toInt() == -1)
			it = fields.remove(it);
		else
			it++;
	
	buildTablequery = "SELECT ID ";
	buildTablequery += " FROM players ";

	if( fields.count() > 0 )
	{
		QSqlCursor r("position_weight");
		r.select(("positionID = " + positionIDStr));
		r.next();

		buildTablequery += " ORDER BY (";

		//////////////////////////////////////////////////
		//
		//  In this loop I add the included fields to a 
		//  sum of the field value times their weight
		//
		//  This is the first determinate form in the 
		//  ORDER BY clause
		//  
		//////////////////////////////////////////////////

		for(it = fields.begin(); it != fields.end(); it++ )
		{
			if( it != fields.begin())
				buildTablequery += " + ";
			buildTablequery +=  *it ;
			buildTablequery += " * ";
			buildTablequery +=  QString::number(r.value(*it).toDouble());
		}

		buildTablequery += ") DESC ";

		////////////////////////////////////////////////////////
		//
		//  This loop adds the chosen fields, in their order,
		//  to the ORBER BY clause, with ASC added to the age
		//  salary, and health fields
		//
		////////////////////////////////////////////////////////

		for(it = fields.begin(); it != fields.end(); it++ )
		{
			buildTablequery += " , ";
			buildTablequery +=  *it ;
			if(!( *it == "Age" || *it == "Salary" || *it == "Health"))
				buildTablequery += " DESC ";
		}

		buildTablequery += " Limit ";
		buildTablequery += r.value("Lim").toString();
	}

	std::cout << "build Table query set to :" << std::endl << buildTablequery << std::endl;
}

void Position::rebuild() // called when user hits rebuild button
{
	QSqlQuery q;

	q.exec("DELETE from assignments WHERE positionID =" + QString::number(positionID) );
	rebuildAssignmentsTable();
	if(! cursor->exec(fetchTablequery) )
		SqlBomb("Position A", fetchTablequery);
	table->refresh();
	emit changed();
}

void Position::rebuildAssignmentsTable()
{

	QSqlQuery query;
	QSqlQuery insert;
		
	if(! query.exec(buildTablequery) )
	{
		QMessageBox::critical(0, "Error in buildTablequery", QSqlDatabase::database()->lastError().text());
		qApp->quit();
	}

	int idx=0;
	while(query.next())
	{
		insert.prepare("INSERT into assignments( ID, positionID, depth )" 
				"VALUES (?,?,?)" );
		insert.bindValue( 0, query.value(0) );
		insert.bindValue(1, positionID);
		insert.bindValue(2, idx);
		if(! insert.exec() )
		{
			QMessageBox::critical(0, "Error in Insert", QSqlDatabase::database()->lastError().text());
			qApp->quit();
		}
			

		idx++;
	}
}
void Position::refreshTable()
{
/*	if(table)
		delete table;
	if(cursor)
		delete cursor;
		
	table = new QDataTable(tableBox);
	cursor = new QSqlSelectCursor();
	if(! cursor->exec(fetchTablequery) )
		SqlBomb("Position B", fetchTablequery);*/
	table->setSqlCursor( cursor, TRUE, TRUE);
	table->setAutoDelete(TRUE);
	table->refresh();
	table->verticalHeader()->hide();
	table->setLeftMargin(0);
/*	for(int idx=0; idx<table->numCols(); idx++)
		table->setColumnStretchable(idx, TRUE);
*/	for(int idx=0; idx<table->numCols(); idx++)
		table->adjustColumn(idx);
}

void Position::up()
{
	QSqlRecord *record;
	QSqlQuery *q;
	int selectedPlayerID;
	int selectedPlayerDepth;
	int secondPlayerID;
	int secondPlayerDepth;
	

	record = table->currentRecord(); // this pointer is owned by table
					// DO NOT DELETE IT
	
	if(record == 0)
		return; // the pointer is 0 if no record has been selected;

	QString selectedPlayerName = record->value("Name").toString();
	selectedPlayerName = selectedPlayerName.prepend("'");
	selectedPlayerName = selectedPlayerName.append("'");
	
	q = new QSqlQuery;
	q->setForwardOnly(TRUE);
	if(!q->exec("SELECT p.ID, a.Depth FROM players p, assignments a WHERE p.ID = a.ID AND p.Name =" + selectedPlayerName + " AND a.positionID =" + QString::number(positionID  )))
	{
		delete q; //must delete first because QSql should not return
		SqlBomb("Position C","Cannot Fetch Player Name");
	}
	if(q->isActive())
		q->next();
	else
	{
		delete q;
		SqlBomb("Position C1","Cannot Fetch Player Name");
	}
	if(q->isValid())
	{
		selectedPlayerID = q->value(0).toInt();
		selectedPlayerDepth = q->value(1).toInt();
	}
	else
	{
		delete q;
		SqlBomb("Position C2","Cannot Fetch Player Name");
	}
	delete q;

	if(selectedPlayerDepth==0)
		return;

	secondPlayerDepth = selectedPlayerDepth -1;
	q = new QSqlQuery;
	q->setForwardOnly(TRUE);
	if(!q->exec("Select ID FROM assignments WHERE positionID = " + QString::number(positionID) + " AND depth = " + QString::number(secondPlayerDepth)))
	{
		delete q;
		SqlBomb("Position D", "Cannot fetch secondPlayerID");
	}
	if(q->isActive())
		q->next();
	else
	{
		delete q;
		SqlBomb("Position D1","Cannot Fetch secondPlayerID");
	}
	if(q->isValid())
		secondPlayerID = q->value(0).toInt();
	else
	{
		delete q;
		SqlBomb("Position D2","Cannot Fetch secondPlayerID");
	}
	delete q;
			

	if(!QSqlDatabase::database()->commit())
		SqlBomb("Position D3", "Cannot Execute commit");
	
	q = new QSqlQuery;
	if(!q->exec("UPDATE assignments SET depth = depth -1 WHERE ID = " + QString::number(selectedPlayerID) + " AND positionID =" + QString::number(positionID)))
	{
		delete q;
		SqlBomb("position E", "Cannot Execute Update");
	}
	if(q->numRowsAffected()!=1)
	{
		delete q;
		SqlBomb("position E1", "Improper Update");
	}
	delete q;

	q = new QSqlQuery;
	if(!q->exec("UPDATE assignments SET depth = depth +1 WHERE ID = " + QString::number(secondPlayerID) + " AND positionID =" + QString::number(positionID)))
	{
		delete q;
		QSqlDatabase::database()->rollback();
		SqlBomb("position F", "Cannot Execute Update");
	}
	if(q->numRowsAffected()!=1)
	{
		delete q;
		QSqlDatabase::database()->rollback();
		SqlBomb("position F1", "Improper Update");
	}
	delete q;
	if(!QSqlDatabase::database()->commit())
		SqlBomb("Position G", "Cannot Execute commit");

	table->refresh();
	table->selectRow(table->currentRow() -1);

	emit changed();
}

void Position::down()
{
	QSqlRecord *record;
	QSqlQuery *q;
	int selectedPlayerID = 0;
	int selectedPlayerDepth = 0;
	int secondPlayerID = 0;
	int secondPlayerDepth;
	int Max = 0;
	QString selectedPlayerName;

//////////////////////////////////////////////////
//
//     Determine if a line has been selected.
//     If Not, exit
//
//////////////////////////////////////////////////


	record = table->currentRecord(); // this pointer is owned by table
					// DO NOT DELETE IT
	
	if(record == 0)
		return; // the pointer is 0 if no record has been selected;
	

//////////////////////////////////////////////////
//
//    Get the name of the selected player
//
//////////////////////////////////////////////////

	selectedPlayerName = record->value("Name").toString();
	selectedPlayerName = selectedPlayerName.prepend("'");
	selectedPlayerName = selectedPlayerName.append("'");
	
//////////////////////////////////////////////////
//
//	Create and execute a query to determine
//	the player's ID, the player's depth for 
//	this position, and the max depth of any
//	player in this position.
//
//	Then vigorously error check the query
//
//	If successful, assign the results to 
//	variables
//
//////////////////////////////////////////////////

	q = new QSqlQuery;
	q->setForwardOnly(TRUE);
	if(!q->exec("SELECT p.ID, a.Depth FROM players p, assignments a WHERE p.ID = a.ID AND p.Name =" + selectedPlayerName + " AND a.positionID =" + QString::number(positionID  )))
	{
		delete q; //must delete first because QSql should not return
		SqlBomb("Position C","Cannot Fetch Player Name");
	}
	if(q->isActive())
		q->next();
	else
	{
		delete q;
		SqlBomb("Position C1","Cannot Fetch Player Name");
	}
	if(q->isValid())
	{
		selectedPlayerID = q->value(0).toInt();
		selectedPlayerDepth = q->value(1).toInt();
	}
	else
	{
		delete q;
		SqlBomb("Position C2","Cannot Fetch Player Name");
	}
	delete q;

//////////////////////////////////////////////////////
//
//	Find maximum depth of players
//	in this position
//
//////////////////////////////////////////////////////


	q = new QSqlQuery;
	q->setForwardOnly(TRUE);
	if(!q->exec("SELECT MAX(depth) FROM  assignments  WHERE  positionID =" + QString::number(positionID  )))
	{
		delete q; //must delete first because QSql should not return
		SqlBomb("Position CA","Cannot Fetch Player Name");
	}
	if(q->isActive())
		q->next();
	else
	{
		delete q;
		SqlBomb("Position CC1","Cannot Fetch Player Name");
	}
	if(q->isValid())
	{
		Max = q->value(0).toInt();
	}
	else
	{
		delete q;
		SqlBomb("Position C2","Cannot Fetch Player Name");
	}
	delete q;

////////////////////////////////////////////
//
//	Now that we know the Depth of the
//	selected player,
//
//	see if it is = to the Max Depth
//	If so, the player cannot be set any
//	lower, so exit
//	
////////////////////////////////////////////

	if(selectedPlayerDepth==Max)
		return;

/////////////////////////////////////////
//
//	Find the ID of the player whom
//	the selected player will be 
//	switching places with by executing 
//	a query based on the depth
//	relative to the selected player.
//
///////////////////////////////////////////

	secondPlayerDepth = selectedPlayerDepth +1;
	q = new QSqlQuery;
	q->setForwardOnly(TRUE);
	if(!q->exec("Select ID FROM assignments WHERE positionID = " + QString::number(positionID) + " AND depth = " + QString::number(secondPlayerDepth)))
	{
		delete q;
		SqlBomb("Position D", "Cannot fetch secondPlayerID");
	}
	if(q->isActive())
		q->next();
	else
	{
		delete q;
		SqlBomb("Position D1","Cannot Fetch secondPlayerID");
	}
	if(q->isValid())
		secondPlayerID = q->value(0).toInt();
	else
	{
		delete q;
		SqlBomb("Position D2","Cannot Fetch secondPlayerID");
	}
	delete q;
			

/////////////////////////////////////
//
//	Imformation gathered.
//	Now prep the transactions,
//	then do the updates.
//
///////////////////////////////////////

	if(!QSqlDatabase::database()->commit())
		SqlBomb("Position D3", "Cannot Execute commit");
	
	q = new QSqlQuery;
	if(!q->exec("UPDATE assignments SET depth = depth +1 WHERE ID = " + QString::number(selectedPlayerID) + " AND positionID =" + QString::number(positionID)))
	{
		delete q;
		SqlBomb("position E", "Cannot Execute Update");
	}
	if(q->numRowsAffected()!=1)
	{
		delete q;
		SqlBomb("position E1", "Improper Update");
	}
	delete q;

	q = new QSqlQuery;
	if(!q->exec("UPDATE assignments SET depth = depth -1 WHERE ID = " + QString::number(secondPlayerID) + " AND positionID =" + QString::number(positionID)))
	{
		delete q;
		QSqlDatabase::database()->rollback();
		SqlBomb("position F", "Cannot Execute Update");
	}
	if(q->numRowsAffected()!=1)
	{
		delete q;
		QSqlDatabase::database()->rollback();
		SqlBomb("position F1", "Improper Update");
	}
	delete q;
	if(!QSqlDatabase::database()->commit())
		SqlBomb("Position G", "Cannot Execute commit");
///////////////////////////////////////
//
// 	All database work is done.
// 	Only thing left is to refresh
//	the table
//
///////////////////////////////////////

	table->refresh();
	table->selectRow(table->currentRow() +1);

	emit changed();
}

void Position::top()
{
	while(table->currentRow()>0)
		up();
}

void Position::remove()
{
	QSqlRecord *record;
	QSqlQuery *q;
	int selectedPlayerID = 0;
	QString delString;
	QString selectedPlayerName;

	record = table->currentRecord(); // this pointer is owned by table

	if(record == 0)
		return; // the pointer is 0 if no record has been selected;

	while(table->currentRow()<table->numRows()-1)
		down();

	selectedPlayerName = record->value("Name").toString();
	selectedPlayerName = selectedPlayerName.prepend("'");
	selectedPlayerName = selectedPlayerName.append("'");

	q = new QSqlQuery;
	q->setForwardOnly(TRUE);
	if(!q->exec("SELECT ID FROM players WHERE Name =" + selectedPlayerName))
	{
		delete q; //must delete first because QSql should not return
		SqlBomb("Position C","Cannot Fetch Player Name");
	}
	if(q->isActive())
		q->next();
	else
	{
		delete q;
		SqlBomb("Position C1","Cannot Fetch Player Name");
	}
	if(q->isValid())
		selectedPlayerID = q->value(0).toInt();
	else
	{
		delete q;
		SqlBomb("Position C2","Cannot Fetch Player Name");
	}
	delete q;

	delString="DELETE FROM assignments WHERE ID =";
	delString+=QString::number(selectedPlayerID);
	delString+=" AND positionID =" + QString::number(positionID);

	q = new QSqlQuery;
	if(!q->exec(delString))
		SqlBomb("Delete Failed", "Cannot Execute Delete Player");
	delete q;

	table->refresh();
	emit changed();
}


void Position::SqlBomb(QString position, QString Description)
{
	{
		QString s = QSqlDatabase::database()->lastError().databaseText();
		Description = Description + "\n\n\n" + s;
		QMessageBox::critical(0, position, Description);
		qApp->quit();
	}
}

