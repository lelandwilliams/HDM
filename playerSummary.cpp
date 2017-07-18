#include"playerSummary.h"


PlayerSummary::PlayerSummary(QWidget *parent, const char* name) : QVGroupBox( parent, name)
{
	table = new QDataTable(this);
	table->setNullText("");
	buildSummaryTable();
	cursor = new QSqlCursor("summary");
	cursor->setMode(QSqlCursor::ReadOnly);
	table->setSqlCursor( cursor, TRUE, TRUE);
	table->setAutoDelete(TRUE);
	table->refresh();
	table->adjustColumn(0);
}

void PlayerSummary::rebuild()
{
	buildSummaryTable();
	table->refresh();
}


QString PlayerSummary::positionName(int positionID)
{
	QSqlQuery sql("SELECT positionName FROM positions WHERE positionID =" + QString::number(positionID) );
	if(!sql.next())
		SqlBomb("Player Summary Error C", "Could not retrieve Position Name");

	return(sql.value(0).toString() );
}

void PlayerSummary::buildSummaryTable()
{
	QSqlQuery * q;
	//int lastID;
	
	// 
	// Create table for view
	//
	q = new QSqlQuery;
	q->exec("DELETE FROM summary");
	delete q;

	q = new QSqlQuery;
	if(!q->exec("SELECT DISTINCT ID from assignments ORDER BY depth"))
		SqlBomb("PlayerSummary A","Select Statement Error");
	while(q->next())
	{
		QSqlQuery sql;
		sql.prepare("INSERT INTO summary (Name, position1, position2, position3) VALUES (?,?,?,?) ");
		
		for(int i=0;i<4;i++)
			sql.bindValue(i, "");
		
		QSqlQuery fetchName("SELECT Name FROM players WHERE ID=" + q->value(0).toString() );
		if(!fetchName.next())
			SqlBomb("PlayerSummary B", "Select Name Error");
		sql.addBindValue(fetchName.value(0).toString());

		QSqlQuery getPositions("Select depth, positionID FROM assignments WHERE ID =" + q->value(0).toString() );
		if(!getPositions.isActive())
			SqlBomb(" PlayerSummary C", "Select depth, positionID error");

		while(getPositions.next())
			sql.addBindValue( positionName( getPositions.value(1).toInt() ) + 
						QString::number(getPositions.value(0).toInt()+ 1) );

		sql.exec();
	}
	delete q;
	
	q = new QSqlQuery();
	if(!q->exec(" INSERT INTO summary (Name)"
			  " SELECT DISTINCT Name"
			  " FROM players"
			  " WHERE ID NOT IN(SELECT DISTINCT ID FROM assignments)"))
	{
		delete q;
		SqlBomb("PlayerSummary Error D", "Cannot Insert inactive players into summary");
	}

}


void PlayerSummary::SqlBomb(QString position, QString Description)
{
	{
		QString s = QSqlDatabase::database()->lastError().databaseText();
		Description = Description + "\n\n\n" + s;
		QMessageBox::critical(0, position, Description);
		qApp->quit();
	}
}
