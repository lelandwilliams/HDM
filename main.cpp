#include<iostream>
#include<qapplication.h>
#include<qtabwidget.h>
#include<qmessagebox.h>
#include<qsqlquery.h>
#include<qptrlist.h>
#include<qdom.h>
#include"position.h"
#include"playerSummary.h"
#include"hdm.h"
#include"mainWindow.h"
#include"firstTimeWizard.h"
#include"databaseConnection.h"


int main( int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFile rcFile(".hdmrc");
	if(!rcFile.open(IO_ReadOnly))
	{
		FirstTimeWizard wizard;
	//	rcFile.close();
	}
	
	QDomDocument doc;
	//rcFile.open(IO_ReadOnly);
	doc.setContent( &rcFile );

	QDomElement root = doc.documentElement();
	if(root.tagName() != "hdmconfig" )
		std::cout << "Error in .hdmconfig" ;
	for( QDomNode curNode = root.firstChild(); !curNode.isNull(); curNode = curNode.nextSibling() )
	{
		QDomElement curElement = curNode.toElement();
		if(! curElement.isNull())
		{
			if( curElement.tagName() == "databaseType" && !curElement.text().isNull() )
				DatabaseConnection::setDatabase(curElement.text());
			if( curElement.tagName() == "username" && !curElement.text().isNull() )
				DatabaseConnection::setUserName(curElement.text());
			if( curElement.tagName() == "server" && !curElement.text().isNull() )
				DatabaseConnection::setServer(curElement.text());
			if( curElement.tagName() == "password" && !curElement.text().isNull() )
				DatabaseConnection::setPassword(curElement.text());
		}

	}
	DatabaseConnection::connect();
	rcFile.close();


	mainWindow *m = new mainWindow();
	
	QPtrList<Position> positions;
	HDM::createConnection();

	QSqlQuery q;
	q.exec("SELECT positionID, positionName FROM positions");
	while(q.next())
	{
		positions.append( new Position( q.value(0).toInt(), q.value(1).toString() ));
		Position * position;
		position=positions.current();
		m->tab->addTab(position, position->getName());
	}

	PlayerSummary *sumTable;
	sumTable = new PlayerSummary();
	m->tab->addTab(sumTable, "Summary");
	m->tab->setFocus();

/*	for( uint idx =0; idx!= m->positions.count(); idx++)
		if(m->positions.at(idx))
			QObject::connect(m->positions.at(idx), SIGNAL(changed()), sumTable, SLOT(rebuild()) );
*/

	positions.first();
	while(positions.current())
	{
		QObject::connect(positions.current(), SIGNAL(changed()), sumTable, SLOT(rebuild()) );
		positions.next();
	}

	app.setMainWidget(m);
	m->setCaption("HDM - Hatrick Depth Manager");
	m->show();

	return app.exec();
}
