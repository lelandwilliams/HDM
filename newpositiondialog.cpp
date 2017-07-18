#include "newpositiondialog.h"


newPositionDialog::newPositionDialog(QWidget *parent, const char *name, bool modal, WFlags f) : QDialog(parent,name,modal,f)
//newPositionDialog::newpositiondialog(QWidget *parent, const char *name) : QDialog(parent,name)
{
	setCaption("Name New Position");
	l = new QVBoxLayout(this);

	label = new QLabel(this);
		label->setText(" Enter the name for this new position");
	eb = new QLineEdit("NewPosition",this);
	
	l->addWidget(label);
	l->addWidget(eb);

	bb = new QHBoxLayout();

	good = new QPushButton("Enter",this );
	cancel = new QPushButton("Cancel", this);

	bb->addWidget(good);
	bb->addWidget(cancel);

	l->addLayout(bb);

	connect( good, SIGNAL(clicked()), this, SLOT(accept()) );
	connect( cancel, SIGNAL(clicked()), this, SLOT(reject()) );
}
