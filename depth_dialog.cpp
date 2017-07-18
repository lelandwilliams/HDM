#include"depth_dialog.h"

depthDialog::depthDialog(int ID, QWidget *parent, const char *name, bool modal, WFlags f) : QDialog(parent,name,modal,f)
{

	HDM::startTransaction();
	delTmp();

	positionID = ID;
	selectStr = "positionID=" + QString::number(ID);

	buildTmpTable();
	buildWidget();

}

depthDialog::depthDialog(QWidget *parent, const char *name, bool modal, WFlags f) : QDialog(parent,name,modal,f)
{
	HDM::startTransaction();
	delTmp();


////////////////////////////////////////////////////////////////
//
//	Create a entry in the positions table to recive
//	  the new position
//
////////////////////////////////////////////////////////////////

	QSqlQuery qa("INSERT INTO positions (positionName) VALUES ('Position Name')");
	/*QSqlCursor *cur1 = new QSqlCursor("positions");
	cur1->primeInsert();
	cur1->setValue("positionName", "NewPosition");
	cur1->insert();
*/

////////////////////////////////////////////////////////////////
//
//	Fetch the key of the new position
//
////////////////////////////////////////////////////////////////

/*	QSqlQuery q1("SELECT LAST_INSERT_ID()");
	if(q1.next())
	{
		positionID = q1.value(0).toInt();
		selectStr = "positionID= " + QString::number(positionID);
	}
	else
		HDM::SqlBomb("","");
*/

	QSqlQuery q1("SELECT positionID FROM positions WHERE positionName = 'Position Name'"); 
	if(q1.next())
	{
		positionID = q1.value(0).toInt();
		selectStr = "positionID= " + QString::number(positionID);
	}
	else
		HDM::SqlBomb("error in DD consructor", "No positionID Available");
	
////////////////////////////////////////////////////////////////
//
//	Create new entries in hattrick.position_order
//	and hattrick.position_weight
//
////////////////////////////////////////////////////////////////

	QSqlQuery q2("INSERT INTO position_weight (positionID) Values (" + QString::number(positionID) + ")");
	QSqlQuery q3("INSERT INTO position_order (positionID) Values (" + QString::number(positionID) + ")");
	
	buildTmpTable();
	buildWidget();
}


void depthDialog::buildTmpTable()
{


	QSqlQuery sql;
	QSqlCursor fetchCursor("position_order");
		fetchCursor.select(selectStr);
		fetchCursor.next();
	QSqlCursor fetchWeightCursor("position_weight");
		fetchWeightCursor.select(selectStr); 
		fetchWeightCursor.next();

	QStringList positionlist = fetchCursor.toStringList();

	for(QStringList::Iterator it = positionlist.begin(); it!=positionlist.end(); ++it)
	{
		if(*it !="positionID")
		{
			QSqlQuery sql;
			sql.prepare("INSERT INTO tmp (Name, fieldOrder, Weight) VALUES(?,?,?)");
			sql.bindValue(0, *it);
			sql.bindValue(1, fetchCursor.value(*it).toString());
			sql.bindValue(2, fetchWeightCursor.value(*it).toString());
			sql.exec();
		}
	}
			
}

void depthDialog::buildWidget()
{
	tablebox = new QVBoxLayout(this);
	textEditBox = new QHBoxLayout(tablebox);
	setupBox = new QHBoxLayout(tablebox);

	unselectedStrList= new QStringList();

/*	query = new QSqlQuery();
	if(!(query->exec("SELECT Name FROM tmp WHERE fieldOrder = -1")));
		HDM::SqlBomb("depth_dialog A : Couldn't read tmp Table", query->lastError().text());
*/
	query = new QSqlQuery("SELECT Name FROM tmp WHERE fieldOrder = -1");

	if(query->isActive())
	{
		while(query->next())
			unselectedStrList->append(query->value(0).toString());
		delete query;
	}

	listBox = new QListBox();
		listBox->insertStrList(unselectedStrList);
		listBox->show();

	cursor = new QSqlCursor("tmp");
		cursor->select("fieldOrder > -1");
		QSqlIndex idx = cursor->index(cursor->toStringList());
		idx.setDescending(1,TRUE);
			


	table = new QDataTable(cursor);
		table->addColumn("Name","Name");
		table->setColumnReadOnly(0, TRUE);
		table->addColumn("Weight","Weight");
		table->setAutoDelete(TRUE);
		table->refresh();
		table->verticalHeader()->hide();
		table->setLeftMargin(0);
		table->show();

	setupBox->addWidget(listBox);
	setupBox->addWidget(table);
}

void depthDialog::delTmp()
{

	QSqlQuery del;
	del.exec("DELETE FROM tmp");
}
		

	
