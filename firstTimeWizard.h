#ifndef HDM_FIRSTTIMEWIZARD
#define HDM_FIRSTTIMEWIZARD

#include<qwizard.h>
#include<qhbox.h>
#include<qvbox.h>
#include<qlayout.h>
#include<qlineedit.h>
#include<qlabel.h>
#include<qcombobox.h>
#include<qlineedit.h>
#include<qwidget.h>


class FirstTimeWizard : QWizard
{
	Q_OBJECT

	public:
	FirstTimeWizard(QWidget* parent=0, const char *name=0);
	void showPage(QWidget* page);

	private:
	void setPageOne();
	void setPageTwo();
	void setPageThree();
	void setPageFour();

	QHBox * pageOne;
	QWidget * pageTwo;
	QHBox * pageThree;
	QHBox * pageFour;

	QComboBox * databaseSelect;
	QLineEdit * server;
	QLineEdit * username;
	QLineEdit * password;

	private slots:
//	void serverChanged(QString serverName);
	//void makeConnection();
};

#endif
