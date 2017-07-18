#ifndef PLAYERSUMMARY_H
#define PLAYERSUMMARY_H
#include<qsqlcursor.h>
#include<qapplication.h>
#include<qdatatable.h>
#include<qsqlquery.h>
#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qstring.h>
#include<qvgroupbox.h>
#include<qhbox.h>

class PlayerSummary : public QVGroupBox
{
	Q_OBJECT

	public:
		
	PlayerSummary(QWidget *parent=0, const char* name=0);
	
	public slots:
		
	void buildSummaryTable();
	void rebuild();

	private:
	
	QDataTable * table;
	QHBox * tableBox;
	QSqlCursor * cursor;

	void SqlBomb(QString a, QString b);
	QString positionName(int positionID);
	

};

#endif
