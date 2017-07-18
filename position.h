#ifndef POSITION_H
#define POSITION_H
#include<qapplication.h>
#include<qdatatable.h>
#include<qsqlselectcursor.h>
#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qstring.h>
#include<qstringlist.h>
#include<qmap.h>
#include<qvgroupbox.h>
#include<qhbox.h>
#include<qpushbutton.h>
#include<qsqlquery.h>
#include<iostream>

typedef QMap<QString, int> orderMap;

class Position : public QVGroupBox
{
	Q_OBJECT
		
	public:

	Position(int a, QString b, QWidget *parent = 0, const char *name = 0);
	QString getName(){ return positionName;}

	public slots:
	
	void up();
	void down();
	void top();
	void remove();
	void rebuild();

	signals:

	void changed();

	private:

	QSqlSelectCursor * cursor;
	int positionID;
	QString positionIDStr;
	int limit;
	QString positionName;
	QString buildTablequery;
	QString fetchTablequery;
	QHBox *tableBox;
	QDataTable * table;
	QHBox *buttonBox;
	QPushButton *upButton;
	QPushButton *downButton;
	QPushButton *topButton;
	QPushButton *deleteButton;
	QPushButton *addButton;
	QPushButton *rebuildButton;

	void testQuery();
	void SqlBomb(QString a, QString b);
	void refreshTable();
	void buildTable();
	void rebuildAssignmentsTable();
	void setBuildTableQuery();
	void setFetchTableQuery();
};
#endif
