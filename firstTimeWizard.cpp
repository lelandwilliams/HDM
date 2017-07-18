#include"firstTimeWizard.h"

FirstTimeWizard::FirstTimeWizard(QWidget *parent, const char *name) : QWizard( parent, name, TRUE)
{
	setPageOne();
	setPageTwo();
	setPageThree();
	setPageFour();
	showPage(pageOne);
	exec();
}

///////////////////////////////////////////////////////////////////////////
//  
//  By overriding the default QWizard::showPage()
//  function, I can catch if the user is ready for pageThree,
//  and if so, I can execute the system() function before showing 
//  the page.
//
////////////////////////////////////////////////////////////////////////////

void FirstTimeWizard::showPage(QWidget* page)
{
	if(page == pageThree)
		{
			QString hostStr = QString::null ;
			if(!server->text().isNull() && server->text() != "localhost")
				hostStr = QString("-h %1" ).arg(server->text());

			QString sysStr = QString("mysql -u %1 -p %2 %3 << hdm_ddl.sql") .arg(username->text()) .arg(password->text() .arg(hostStr));
			int error = std::system(sysStr);
			if( error == -1)
				QWizard::showPage(pageThree);
			else
				QWizard::showPage(pageFour);
		}
	QWizard::showPage(page);
}

void FirstTimeWizard::setPageOne()
{
	pageOne = new QHBox( this );
	QLabel * label = new QLabel(pageOne);
	label->setText("This appears to be the first time you \n"
			"have used the Hattrick Depth Manager\n\n"
			"This Wizard will help you set up your database\n"
			"And create it's configuration files\n\n\n"
			"Press the Next button to continue");

	addPage(pageOne, "Intro");

	setBackEnabled(pageOne,false);
	setNextEnabled(pageOne,true);
	setHelpEnabled(pageOne,false);
	setFinishEnabled(pageOne,false);
}


void FirstTimeWizard::setPageTwo()
{
	pageTwo = new QWidget( this );


//	databaseLabel->setMinimumWidth(usernameLabel->sizeHint().width());
//	serverLabel->setMinimumWidth(usernameLabel->sizeHint().width());
//	usernameLabel->setMinimumWidth(usernameLabel->sizeHint().width());
//	passwordLabel->setMinimumWidth(usernameLabel->sizeHint().width());

	QLabel * databaseLabel = new QLabel(pageTwo);
			databaseLabel->setAlignment(Qt::AlignVCenter);
	databaseSelect = new QComboBox(pageTwo);
		databaseSelect->insertItem("MySql");
	QLabel * serverLabel = new QLabel("server",pageTwo);
		serverLabel->setAlignment(Qt::AlignVCenter);
	//QPushButton * connectButton = new QPushButton("Connect", pageTwo);
	//	connect(connectButton,clicked(),this, makeConnection());

	server = new QLineEdit(pageTwo);


	QHBoxLayout* line1 = new QHBoxLayout();
		line1->addWidget(databaseLabel);
		line1->addWidget(databaseSelect);
	QHBoxLayout* line2 = new QHBoxLayout();
		line2->addWidget(serverLabel);
		line2->addWidget(server);
	QHBoxLayout* line3 = new QHBoxLayout();
		QLabel * usernameLabel = new QLabel("user name",pageTwo);
			usernameLabel->setAlignment(Qt::AlignVCenter);
		line3->addWidget(usernameLabel);
		username = new QLineEdit(pageTwo);
		line3->addWidget(username);
	QHBoxLayout* line4 = new QHBoxLayout();
		QLabel * passwordLabel = new QLabel("password",pageTwo);
			passwordLabel->setAlignment(Qt::AlignVCenter);
		line4->addWidget(passwordLabel);
		password = new QLineEdit(pageTwo);
			password->setEchoMode(QLineEdit::Password);
		line4->addWidget(password);
	
	QVBoxLayout * formBox = new QVBoxLayout();
		formBox->setMargin(11);
		formBox->addLayout(line1);
		formBox->addLayout(line2);
		formBox->addLayout(line3);
		formBox->addLayout(line4);
	//	formBox->addWidget(connectButton);

	QLabel * pageInfo = new QLabel(pageTwo);
	pageInfo->setText("<h2>Enter Database Info</h2> <p>please enter your connection info for a MySql database.</p> "
			"<p>HDM will attempt to connect to the database, and, if successful, create the required database tables.</p>");

	/*pageInfo->setText("Enter the information about your database\n\n"
			"At This time HDM only supports MySQL\n\n"
			"HDM asks for your username and password\n"
			"of a MySql account so that it can set up\n"
			"it's own username, and database tables\n"
			"and will not keep this info");
	*/

	QHBoxLayout * mainLayout = new QHBoxLayout(pageTwo);
		mainLayout->addWidget(pageInfo);
		mainLayout->addStretch(4);
		mainLayout->addLayout(formBox);

	addPage(pageTwo, "Enter Database Info");

	setBackEnabled(pageTwo,true);
	setNextEnabled(pageTwo,false);
	setHelpEnabled(pageTwo,true);
	setFinishEnabled(pageTwo,false);
}

void FirstTimeWizard::setPageThree()
{
	pageThree = new QHBox(this);
	QLabel * pageThreeLabel = new QLabel(pageThree);
		 pageThreeLabel->setText("<h2>Error</h2>"
		"<p>HDM was unable to connect to the database.</p>"
		"<p>Please press the Back button and re-enter the info</p>"
		"<p>and be certain to start the database server, if it has not been allready");
	
	addPage(pageThree,"Database Configuration Unsucessful");
	setNextEnabled(pageThree, false);
	setBackEnabled(pageThree, true);
}

void FirstTimeWizard::setPageFour()
{
	pageFour = new QHBox(this);
	QLabel *pageFourLabel = new QLabel(pageFour);
		pageFourLabel->setText("<h2> Success! </h2>"
				"<p>HDM's database tables were successfully created and you"
				"are now ready to use HDM. Probably the first thing you should"
				"do is download your player info.<p>");
	setBackEnabled(pageFour, false);
	setFinishEnabled(pageFour, true);
	addPage(pageFour, "Success");
}


