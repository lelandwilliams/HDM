#ifndef NEWPOSITIONDIALOG_H
#define NEWPOSITIONDIALOG_H

#include <qlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qdialog.h>
#include <qlineedit.h>


class newPositionDialog : public QDialog
{

	public:    
	newPositionDialog( bool edit = false; QWidget *parent=0, const char *name=0, bool modal=TRUE, WFlags f = 0);
	QString name(){return eb->text();}

	private:
	QVBoxLayout *l;
	QHBoxLayout *bb;
	QLabel *label;
	QPushButton *good;
	QPushButton *cancel;
	QLineEdit *eb;
};

#endif

