#ifndef POSITIONDIALOG_H
#define POSITIONDIALOG_H

#include <qdialog.h>
#include <qhgroupbox.h>
#include <qvgroupbox.h>
#include <qlistbox.h>
#include <qmap.h>
#include <qsqlcursor.h>
#include <qstringlist.h>
#include <iostream>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>

typedef QMap<QString, int> orderMap;

class PositionElementLine: public QObject
{
	Q_OBJECT

	public:

	PositionElementLine(QString n, int pos; bool checked = false; QWidget *parent = 0; const char *name = 0;)
	QString getName() {return name;}
	void setName(QString n) {name = n;}
	int getPosition() {return position;}
	void setPosition(int p) {return p;} 

	private:

	QString name;
	int position; 

	QVBoxLayout *layout;
	QSpinBox *spinBox;
	QCheckBox *checkBox;
	QPushButton *upButton;
	QPushButton *downButton;

	public signals:

	void changed();
	void moveUp();
	void moveDown();
};

class positionDialog :  public QDialog
{
	Q_OBJECT
		
	public:
		
	positionDialog(QString PositionName="Losers", int positionID = -1, QWidget *parent=0, const char *name=0, bool modal=TRUE, WFlags f = 0);

	QStringList shownFields; // an ordered list of the fields used to determine importance of players
	QStringList unusedFields; // an unordered list of the fields not presently used
	QString name; 		// name of the position
	bool nameChanged;
	bool listChanged;
	bool newPosition;

	public slots:

	void addLabel();
	void up();
	void down();
	void remove();
	void updateList();
	void updateName(const QString & newName);

	private:
	QVBoxLayout 	*mainbox;
	QHBoxLayout 	*upperbox;
	QVBoxLayout 	*bb1;
	QVBoxLayout 	*bb2;
	QPushButton 	*removeButton;
	QPushButton 	*upButton;
	QPushButton 	*downButton; 
//	QGroupBox 	*lowerbox;
	QPushButton 	*addButton; 
	QHBoxLayout 	*endDialogButtonBox;
	QHBoxLayout	*editBoxLayout;
	QPushButton 	*commitButton; 
	QPushButton 	*cancelButton; 
	QListBox	*shownFieldsListBox;
	QListBox	*unusedFieldsListBox;
	QLabel		*editBoxLabel;
	QLineEdit	*editBox;
	void generateLists();
	QStringList fields;
	QString positionIDStr;

};
#endif
