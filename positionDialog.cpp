#include "positionDialog.h"

positionDialog::positionDialog(QString PositionName, int positionID, QWidget *parent, const char *name, bool modal, WFlags f) : QDialog(parent,name,modal,f)
{
	nameChanged = false;
	listChanged = false;
	newPosition = false;
	name = PositionName;

	if(positionID == -1)
		newPosition = true;
	else
		positionIDStr = QString::number(positionID);

	generateLists(); // fill in shownFields and unusedFields;

	commitButton = new QPushButton("commit",this, "positiondialogcommitbutton");
	cancelButton = new QPushButton("cancel",this, "positiondialogcancelbutton");
	unusedFieldsListBox = new QListBox(this);
		unusedFieldsListBox->insertStringList(unusedFields);
	addButton = new QPushButton(">>",this, "PositionDialogAddButton");
	removeButton = new QPushButton("<<",this, "positiondialogremovebutton");
	shownFieldsListBox = new QListBox(this);
		shownFieldsListBox->insertStringList(shownFields);
	upButton = new QPushButton("move up",this, "positiondialogupbutton");
	downButton = new QPushButton("move down",this, "positiondialogdownbutton");
	editBox = new QLineEdit(PositionName, this);
	editBoxLabel = new QLabel(this);
		editBoxLabel->setText("Position Name");

	bb1 = new QVBoxLayout();
		bb1->addWidget(addButton);
		bb1->addWidget(removeButton);
	bb2 = new QVBoxLayout();
		bb2->addWidget(upButton);
		bb2->addWidget(downButton);
		//bb2->setSpacing(0);
	editBoxLayout = new QHBoxLayout();
		editBoxLayout->addWidget(editBoxLabel);
		editBoxLayout->addWidget(editBox);
	endDialogButtonBox = new QHBoxLayout();
		endDialogButtonBox -> addWidget(commitButton);
		endDialogButtonBox -> addWidget(cancelButton);
		//endDialogButtonBox -> setSpacing(0);
		endDialogButtonBox -> setMargin(11);
	upperbox = new QHBoxLayout();
		upperbox->addWidget(unusedFieldsListBox);
		upperbox ->addLayout(bb1);
		upperbox->addWidget(shownFieldsListBox);
		upperbox->addLayout(bb2);
	mainbox = new QVBoxLayout(this);
		mainbox->setMargin(11);
		mainbox->setSpacing(6);
		mainbox->addLayout(editBoxLayout);
		mainbox->addLayout(upperbox);
		mainbox->addLayout(endDialogButtonBox);

	addButton->setMaximumWidth(40);	
	removeButton->setMaximumWidth(40);	

	commitButton->setMaximumWidth(upButton->width());
	cancelButton->setMaximumWidth(upButton->width());

	connect ( addButton, SIGNAL(clicked()), this, SLOT(addLabel() ));
	connect ( addButton, SIGNAL(clicked()), this, SLOT(updateList() ));
	connect ( removeButton, SIGNAL(clicked()) , this, SLOT(remove() ));
	connect ( removeButton, SIGNAL(clicked()) , this, SLOT(updateList() ));
	connect ( upButton, SIGNAL(clicked()), this, SLOT(up() ));
	connect ( upButton, SIGNAL(clicked()), this, SLOT(updateList() ));
	connect ( downButton, SIGNAL(clicked()), this, SLOT(down() ));
	connect ( downButton, SIGNAL(clicked()), this, SLOT(updateList() ));
	connect ( commitButton, SIGNAL(clicked()), this, SLOT(accept() ));
	connect ( cancelButton, SIGNAL(clicked()), this, SLOT(reject() ));
	connect ( editBox, SIGNAL(textChanged(const QString &)), this, SLOT(updateName(const QString &) ));
}

void positionDialog::generateLists()
{
/////////////////////////////////////
//
// This method reads the hdm database
// table "position_order" and from it
// gathers two QStringLists:
//
// unusedFields is a list of the strings of fields
// that have been determined to be unimportant to
// that particular position
//
// shownFields is a list of the fields that are pertainant 
// to the position, ordered top to bottom in the order that they
// are displayed in the position
//
///////////////////////////////////////////

	bool debug=false;

	QSqlCursor *cursor= new QSqlCursor("position_order");

	if(!newPosition)
		cursor->select("positionID = " + positionIDStr);

	fields = cursor->toStringList();
	fields.remove("positionID");

	unusedFields.clear();
	if(newPosition)
	{
		shownFields = fields;
	}
	else
	{
		orderMap map;

		while(cursor->next())
			for(QStringList::iterator it = fields.begin(); it != fields.end(); it++)
			{
					if(cursor->value(*it).toInt() == -1 )
						unusedFields += *it;
					else
						map[*it] = cursor->value(*it).toInt();
			}

		for(int curVal = map.count(); curVal !=0; curVal--)
		{
			for(orderMap::iterator it2 = map.begin(); it2 != map.end(); it2++)
				if(it2.data() == curVal)
					shownFields+= it2.key();
		}
	}


	if(debug)
	{ 
		std::cout << std::endl;
		std::cout << " ---- Shown Fields ------" << std::endl;
	
		for(QStringList::iterator it2 = shownFields.begin(); it2 != shownFields.end(); it2++)
			std::cout << *it2 << std::endl ;

	std::cout << std::endl << " ---- Unused Fields ---- " << std::endl;

	for(QStringList::iterator it2 = unusedFields.begin(); it2 != unusedFields.end(); it2++)
		std::cout << *it2 << std::endl ;
	}
}

void positionDialog:: addLabel()
{
	int selected = unusedFieldsListBox->currentItem(); 
	
	if (selected != -1)
	{
		shownFieldsListBox->insertItem( unusedFieldsListBox->currentText(), -1);
		unusedFieldsListBox->removeItem(selected);
	}
}


void positionDialog:: remove()
{
	int selected = shownFieldsListBox->currentItem(); 
	
	if (selected != -1)
	{
		unusedFieldsListBox->insertItem( shownFieldsListBox->currentText(), -1);
		shownFieldsListBox->removeItem(selected);
	}
}

void positionDialog:: up()
{
	int selected = shownFieldsListBox->currentItem(); 
	
	if (selected != -1)
	{
		QString selStr = shownFieldsListBox->currentText();
		shownFieldsListBox->removeItem(selected);
		selected--;
		shownFieldsListBox->insertItem( selStr, selected);
		shownFieldsListBox->setCurrentItem(selected);
	}
}

void positionDialog:: down()
{
	int selected = shownFieldsListBox->currentItem(); 
	
	if (selected != -1)
	{
		QString selStr = shownFieldsListBox->currentText();
		shownFieldsListBox->removeItem(selected);
		selected++;
		shownFieldsListBox->insertItem( selStr, selected);
		shownFieldsListBox->setCurrentItem(selected);
	}
}

void positionDialog::updateList()
{
	listChanged = true;
	shownFields.clear();
	unusedFields.clear();

	QListBoxItem * item = shownFieldsListBox->firstItem();
	while(item)
	{
		shownFields += item->text();
		item=item->next();
	}

	item = unusedFieldsListBox->firstItem();
	while(item)
	{
		unusedFields += item->text();
		item=item->next();
	}

	std::cout << " Lists Updated" << std::endl ;
}

void positionDialog::updateName(const QString & newName)
{
	nameChanged = true;
	name = newName;
	std::cout << " Name is changed to " << name << std::endl;
}

