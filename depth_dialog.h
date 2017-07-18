#ifndef DEPTHDIALOG_H
#define DEPTHDIALOG_H
#include<qdatatable.h>
#include<qsqlcursor.h>
#include<qsqlquery.h>
#include<qlayout.h>
#include<qpushbutton.h>
#include<qstringlist.h>
#include<qstring.h>
#include<qlistbox.h>
#include<qsqlindex.h>
#include "hdm.h"


class depthDialog : public QDialog
{

	public:    
	depthDialog(int ID, QWidget *parent=0, const char *name=0, bool modal=TRUE, WFlags f=0);
	depthDialog(QWidget *parent=0, const char *name=0, bool modal=TRUE, WFlags f = 0);

	private:
	QDataTable  *table;
	QSqlCursor  *cursor;
	QSqlQuery   *query;
	QString     selectStr;
	QStringList *unselectedStrList;
	QVBoxLayout *tablebox;
	QVBoxLayout *buttonbox;
	QHBoxLayout *textEditBox;
	QHBoxLayout *setupBox;
	QPushButton *addbutton;
	QPushButton *removebutton;
	QListBox    *listBox;

	int positionID;

	void buildTmpTable();
	void buildWidget();
	void delTmp();
};

#endif
