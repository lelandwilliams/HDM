#include"mainWindow.h"

mainWindow::mainWindow(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
	w = new QWidgetStack(this);
	setCentralWidget(w);
	tab = new QTabWidget();
	tab->setMargin(10);

	w->addWidget(tab);
	w->raiseWidget(tab);
	
	QPopupMenu *action = new QPopupMenu();
	menuBar()->insertItem("&Action", action);
		action->insertItem("Define New Position", this, SLOT(newposition()), Key_F2);
		action->insertItem("Download Data", this, SLOT(download()) );
		action->insertItem("Quit", qApp , SLOT(quit()), CTRL+Key_Q);

	QPopupMenu *view = new QPopupMenu();
	menuBar()->insertItem("&View", view);
		view->insertItem("PositionRosters", this, SLOT(viewrosters()) );
		view->insertItem("Lineup", this, SLOT(viewlineup()) );

/*	QSqlQuery q;
	q.exec("SELECT positionID, positionName, buildTableQuery, fetchTableQuery FROM positions");
	while(q.next())
	{
		positions.append( new Position( q.value(0).toInt(), q.value(1).toString(), q.value(2).toString(), q.value(3).toString()));
		Position * position;
		position=positions.current();
		this->tab->addTab(position, position->getName());
	}
*/
}

void mainWindow::newposition()
{

	//dlg = new newPositionDialog();
	dlg = new positionDialog();
	dlg->setModal(TRUE);
	
	if(dlg->exec() == QDialog::Accepted && (dlg->listChanged ||  dlg->nameChanged) && dlg->shownFields.count() )
	{
		QSqlQuery q;
		q.exec("INSERT INTO positions (positionID, positionName) VALUES (NULL, '" + dlg->name + "')"); 
		//q.exec("SELECT positionID FROM positions WHERE positionName =" + dlg->name);
		q.exec("SELECT LAST_INSERT_ID()" );
		q.next();
		int newID = q.value(0).toInt();
		QString newIDStr = QString::number(newID);

		q.exec("INSERT INTO position_order (positionID) VALUES (" + newIDStr + ")");
		q.exec("INSERT INTO position_weight (positionID) VALUES (" + newIDStr + ")");

		int idx = dlg->shownFields.count();
		for( QStringList::Iterator it = dlg->shownFields.begin(); it != dlg->shownFields.end(); it++)
		{
			q.exec("UPDATE position_order SET " + *it + " = " + QString::number(idx) + " WHERE positionID = " + newIDStr);
			idx --;
		}

		Position * newPos = new Position( newID, dlg->name);
		positions.append(newPos); 
		tab->insertTab(newPos, newPos->getName(), (tab->count() -1) );

	}

}

void mainWindow::download()
{
}
void mainWindow::viewrosters()
{
}

void mainWindow::viewlineup()
{
}


