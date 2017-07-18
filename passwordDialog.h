#ifndef PASSWORD_DIALOG_H
#define PASSWORD_DIALOG_H


#include<qdialog.h>
#include<qlayout.h>
#include<qpushbutton.h>
#include<qlineedit.h>
#include<qlabel.h>

class PasswordDialog : public QDialog
{
	public:
	PasswordDialog(QWidget *parent=0, const char *name=0, bool modal = true, WFlags flag=0);
	QString password(){return passEdit->text();}
	QString loginname(){return nameEdit->text();}

	private:
	QVBoxLayout *centralLayout;
	QHBoxLayout *buttonBox;
	QPushButton *acceptButton;
	QPushButton *rejectButton;
	QLabel	*nameLabel;
	QLabel  *passLabel;
	QLineEdit *nameEdit;
	QLineEdit *passEdit;
};

#endif

