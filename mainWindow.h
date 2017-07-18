#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<qmainwindow.h>
#include<qpopupmenu.h>
#include<qmenubar.h>
#include<qapplication.h>
#include<qwidgetstack.h>
#include<qtabwidget.h>
#include<qsqlquery.h>
#include "position.h"
//#include"depth_dialog.h"
#include "newpositiondialog.h"
#include "positionDialog.h"

class mainWindow : public QMainWindow
{
	Q_OBJECT

	public:
	mainWindow(QWidget *parent = 0, const char *name = 0);
	QWidgetStack *w;
	QTabWidget *tab;
	QPtrList<Position> positions;

//	newPositionDialog *dlg;
	positionDialog *dlg;

	public slots:
	void newposition();
	void download();
	void viewrosters();
	void viewlineup();

};

#endif
