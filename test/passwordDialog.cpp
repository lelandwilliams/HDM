#include"passwordDialog.h"

PasswordDialog::PasswordDialog(QWidget *parent, const char *name, bool modal, WFlags f) : QDialog(parent,name,modal,f)
{
	setCaption("Login");
	centralLayout = new QVBoxLayout(this);
	nameLabel = new QLabel("Login Name:",this);
	passLabel = new QLabel("Password:",this);
	nameEdit = new QLineEdit(this);
	passEdit = new QLineEdit(this);
	buttonBox = new QHBoxLayout(this);
	acceptButton = new QPushButton("Login",this);
	rejectButton = new QPushButton("Cancel", this);

	centralLayout->addWidget(nameLabel);
	centralLayout->addWidget(nameEdit);
	centralLayout->addWidget(passLabel);
	centralLayout->addWidget(passEdit);
	buttonBox->addWidget(acceptButton);
	buttonBox->addWidget(rejectButton);
	buttonBox->setMargin(5);
	//centralLayout->insertSpacing(-1,5);
	centralLayout->addLayout(buttonBox);
	centralLayout->setMargin(15);

	connect( acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect( rejectButton, SIGNAL(clicked()), this, SLOT(reject()));
}

